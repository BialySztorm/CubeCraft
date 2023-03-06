// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeCraftGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ACubeCraftGameModeBase::BeginPlay()
{
	Super::BeginPlay();
		SpawnBlocks();
}

void ACubeCraftGameModeBase::SpawnBlocks()
{

	if (BlockRef != NULL)
	{
		FRotator SpawnRotation = { 0.f, 0.f, 0.f };
		FVector SpawnVector;
		float X = -(Depth / 2 * 100 - 50);
		float Y = -(Width / 2 * 100 - 50);
		float Z = 150.f;
		FActorSpawnParameters SpawnInfo;
		for (int32 i = 0; i < Depth; i++)
		{
			for (int32 j = 0; j < Width; j++)
			{
				Z = 150.f;
				for (int32 k = 0; k < Height; k++)
				{
					SpawnVector = { X,Y,Z };
					GetWorld()->SpawnActor<AActor>(BlockRef, SpawnVector, SpawnRotation, SpawnInfo);
					Z += 100.f;
				}
				Y += 100;
			}
			Y = -(Width / 2 * 100 - 50);
			X += 100.f;
		}
	}

}
