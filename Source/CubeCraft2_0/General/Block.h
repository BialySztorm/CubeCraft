// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealNetwork.h"
#include "Block.generated.h"

class UBoxComponent;

UCLASS()
class CUBECRAFT2_0_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetMesh(int32 id);
	
	

	UFUNCTION(BlueprintImplementableEvent)
	void ScratchMaterial();

	UFUNCTION(BlueprintImplementableEvent)
	int32 GetMesh();

	UFUNCTION(BlueprintImplementableEvent)
	TSubclassOf<AActor> GetBlockType();

};
