// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnrealNetwork.h"
#include "Hiter.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CUBECRAFT2_0_API UHiter : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHiter();
	UPROPERTY(BlueprintReadOnly)
	bool IsSetHiter = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		UInputComponent* InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
		float Reach = 200.f;
	UPROPERTY(EditAnywhere)
		float Damage = 50.f;
	UPROPERTY(VisibleAnywhere, Category = "Damage")
		TSubclassOf<UDamageType> DamageType;

	AActor* MyOwner;

	UFUNCTION(BlueprintCallable)
	void SetUpInputComponent();

	FHitResult GetFirstPhisycsBodyInReach() const;

	UFUNCTION(Server,unreliable)
	void Server_Punch(AActor* OtherActor, float Damage1, AController* EventInvestigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageType1);

	void Punch();

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* HitSound;
};
