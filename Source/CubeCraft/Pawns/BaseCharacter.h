// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class ACubeCraftPlayerController;

UCLASS()
class CUBECRAFT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Arms;

	ACubeCraftPlayerController* PlayerControllerRef;


	//void SprintOn();
	//void SprintOff();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookUpPad(float AxisValue);
	void LookAroundPad(float AxisValue);



	UPROPERTY(EditAnywhere)
		float RotationRate = 20;
	UPROPERTY(EditAnywhere)
		float SpeedBoost = 1.f;
	UPROPERTY(EditAnywhere)
		float Speed = 0.3f;

	bool IsMenu = 0;
	void IsMenuActive();
	void ActiveMenu(bool bIsMenuActive);


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void AddToGUI(int32 ID);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
		TSubclassOf<AActor> GetActorType(int32 Type);
	UFUNCTION(BlueprintImplementableEvent)
		void bActiveMenu(bool bIsMenuActive);
	UFUNCTION(BlueprintImplementableEvent)
		void ConfigurateBlueprints();


};
