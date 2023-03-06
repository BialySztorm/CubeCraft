// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CubeCraftGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CUBECRAFT_API ACubeCraftGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void AddToGUI(int32 ID);
	UFUNCTION(BlueprintCallable)
		void SpawnBlocks();
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AActor> BlockRef;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		int32 Depth = 20;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		int32 Width = 20;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		int32 Height = 3;
	

private:
	

protected:
	virtual void BeginPlay() override;
};
