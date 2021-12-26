// Fill out your copyright notice in the Description page of Project Settings.


#include "BrokenBlock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABrokenBlock::ABrokenBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABrokenBlock::BeginPlay()
{
	Super::BeginPlay();
	

	
}

// Called every frame
void ABrokenBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

