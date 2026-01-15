// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "CC_And_IFPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class ACC_And_IFPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* PossessMappingContexts;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* CharMappingContexts;
	
	/** Action */
	UPROPERTY(EditAnywhere, Category="Input|Action")
	UInputAction* PossessAction;
	
	/** Characters Class */
	UPROPERTY(EditAnywhere, Category="Charachter switch")
	TSubclassOf<APawn> CharacterClass;
	
	TSubclassOf<APawn> SpawnedCharacterClass;

	/** Gameplay initialization */
	virtual void BeginPlay() override;
	
	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	
	void PossessPlayer();

};
