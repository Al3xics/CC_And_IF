// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CC_And_IFGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ACC_And_IFGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ACC_And_IFGameMode();
};



