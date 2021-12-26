// Fill out your copyright notice in the Description page of Project Settings.


#include "Hiter.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHiter::UHiter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bReplicates = true;
	// ...
}


// Called when the game starts
void UHiter::BeginPlay()
{
	Super::BeginPlay();


}

void UHiter::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	//UE_LOG(LogTemp, Warning, TEXT("Hiter is working!"));
	if (InputComponent)
	{
		IsSetHiter = 1;
		UE_LOG(LogTemp, Warning, TEXT("Input Component found %S"), *GetOwner()->GetName());
		InputComponent->BindAction("Punch", EInputEvent::IE_Pressed, this, &UHiter::Punch);
		MyOwner = GetOwner();
		
	}
}

FHitResult UHiter::GetFirstPhisycsBodyInReach() const
{
	// PlayerVievport
	FVector EyeVector;
	FRotator EyeRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(EyeVector, EyeRotator);

	FVector LineTrace = EyeVector + EyeRotator.Vector() * Reach;

	FHitResult Hit;
	FCollisionQueryParams TraceParams{ FName(TEXT("")), false, GetOwner() };
	// Ray-cast from distance (Reach)
	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		EyeVector,
		LineTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

void UHiter::Server_Punch_Implementation(AActor* OtherActor, float Damage1, AController* EventInvestigator, AActor* DamageCauser,TSubclassOf<UDamageType> DamageType1 )
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage1, EventInvestigator, DamageCauser, DamageType1);
}

void UHiter::Punch()
{
	FHitResult Hit = GetFirstPhisycsBodyInReach();
	AActor* OtherActor = Hit.GetActor();
	// Checking reference is created
	if (!MyOwner)
		return;
	if (OtherActor && OtherActor != MyOwner)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetOwner()->GetActorLocation());
		Server_Punch(OtherActor, Damage, MyOwner->GetInstigatorController(), this->GetOwner(), DamageType);
	}
}


