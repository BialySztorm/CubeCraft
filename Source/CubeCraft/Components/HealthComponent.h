// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnrealNetwork.h"
#include "HealthComponent.generated.h"

class ABlock;
class ABrokenBlock;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBECRAFT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(Server, unreliable)
	void Server_TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCouser);

private:
	UPROPERTY(EditAnywhere)
		float DefaultHealth = 100.f;
	float Health = 0.f;

	ABlock* BlockRef;
	ABrokenBlock* BrokenBlockRef;
	AActor* TmpAActor;
		
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DestroyParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DestroySound;
	UFUNCTION(NetMulticast, reliable)
		void Client_Effects();
	UFUNCTION(NetMulticast, reliable)
		void Client_Scratch(ABlock* BlockRef2);
};
