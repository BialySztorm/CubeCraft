// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CubeCraftPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CUBECRAFT2_0_API ACubeCraftPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void SetPlayerEnabledState(bool SetPlayerEnabled);
};
