// Copyright Epic Games, Inc. All Rights Reserved.


#include "CC_And_IFPlayerController.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "CC_And_IF.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Input/SVirtualJoystick.h"

void ACC_And_IFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* CurrentPawn = GetPawn();
	if (!CurrentPawn)
	{
		UE_LOG(LogCC_And_IF, Error, TEXT("No pawn found for player controller."));
		return;
	}
	
	UClass* PawnClass = CurrentPawn->GetClass();
	if (!PawnClass)
	{
		UE_LOG(LogCC_And_IF, Error, TEXT("Pawn class is invalid."));
		return;
	}
	
	SpawnedCharacterClass = PawnClass;
}

void ACC_And_IFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContexts, 0);
			Subsystem->AddMappingContext(PossessMappingContexts, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(PossessAction, ETriggerEvent::Triggered, this, &ACC_And_IFPlayerController::PossessPlayer);
	}
}

void ACC_And_IFPlayerController::PossessPlayer()
{
	APawn* CurrentPawn = GetPawn();
	if (!CharacterClass || !SpawnedCharacterClass) return;

	// Current pawn is a BP_ThirdPersonCharacter
	if (CurrentPawn && CurrentPawn->IsA(SpawnedCharacterClass))
	{
		ACharacter* TargetCharacter = nullptr;

		AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), CharacterClass);
		TargetCharacter = Cast<ACharacter>(FoundActor);

		if (!TargetCharacter)
		{
			FVector PlayerSpawnLocation = CurrentPawn->GetActorLocation();
			FRotator SpawnRotation = CurrentPawn->GetActorRotation();
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			TargetCharacter = GetWorld()->SpawnActor<ACharacter>(CharacterClass, PlayerSpawnLocation, SpawnRotation, SpawnParams);
		}

		if (TargetCharacter)
		{
			Possess(TargetCharacter);

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(DefaultMappingContexts);
				Subsystem->AddMappingContext(CharMappingContexts, 0);
			}
		}
	}
	// CurrentPawn is a BP_Char
	else if (CurrentPawn && CurrentPawn->IsA(CharacterClass))
	{
		ACharacter* TargetCharacter = nullptr;

		AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), SpawnedCharacterClass);
		TargetCharacter = Cast<ACharacter>(FoundActor);

		if (!TargetCharacter)
		{
			FVector PlayerSpawnLocation = CurrentPawn->GetActorLocation();
			FRotator SpawnRotation = CurrentPawn->GetActorRotation();
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			TargetCharacter = GetWorld()->SpawnActor<ACharacter>(SpawnedCharacterClass, PlayerSpawnLocation, SpawnRotation, SpawnParams);
		}

		if (TargetCharacter)
		{
			Possess(TargetCharacter);

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(CharMappingContexts);
				Subsystem->AddMappingContext(DefaultMappingContexts, 0);
			}
		}
	}
}
