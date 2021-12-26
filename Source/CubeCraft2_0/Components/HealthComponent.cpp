// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../General/Block.h"
#include "../General/BrokenBlock.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bReplicates = true;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = DefaultHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::Server_TakeDamage);
}

void UHealthComponent::Client_Scratch_Implementation(ABlock* BlockRef2)
{
	BlockRef2 = Cast<ABlock>(GetOwner());
	BlockRef2->ScratchMaterial();
}

void UHealthComponent::Client_Effects_Implementation()
{
	bReplicates = true;
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticle, GetOwner()->GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetOwner()->GetActorLocation());
}



void UHealthComponent::Server_TakeDamage_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCouser)
{
	if (Damage == 0 || Health <= 0)
		return;

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	//UE_LOG(LogTemp,Warning,TEXT("Health:%f"),Health);
	//UE_LOG(LogTemp,Warning,TEXT("Damage:%f"),Damage);
	if (Health <= 0)
	{
		
		BlockRef = Cast<ABlock>(GetOwner());
		int32 ID = BlockRef->GetMesh();
		FActorSpawnParameters SpawnInfo;
		FVector Loc = BlockRef->GetActorLocation();
		FRotator Rot = { 0.f,0.f,0.f };
		TmpAActor = GetWorld()->SpawnActor<AActor>(BlockRef->GetBlockType(), Loc, Rot, SpawnInfo);
		BrokenBlockRef = Cast<ABrokenBlock>(TmpAActor);
		BrokenBlockRef->SetMesh(ID);
		Client_Effects();
		GetOwner()->Destroy();
	}
	else if (Health < 100)
	{
		Client_Scratch(BlockRef);
		
	}
}

