// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Components/MeshComponent.h"
#include "../GameMode/CubeCraftGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Pawns/BaseCharacter.h"

// Sets default values for this component's properties
UPicker::UPicker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bReplicates = true;
}


// Called when the game starts
void UPicker::BeginPlay()
{
	Super::BeginPlay();

	//FindPhysicsHandle();
	BaseCharacterRef = Cast<ABaseCharacter>(GetOwner());
}



//SetUp physics handle input component
void UPicker::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Input Component found %S"), *GetOwner()->GetName());
		InputComponent->BindAction("Pick", IE_Pressed, this, &UPicker::Pick);
		InputComponent->BindAction("Place", IE_Pressed, this, &UPicker::Place);
		InputComponent->BindAction("Release", IE_Pressed, this, &UPicker::Release);
		IsSetPicker = 1;
	}
}

//Grabs items
void UPicker::Pick()
{
	// UE_LOG(LogTemp, Warning, TEXT("Picker Pressed"));

	// Gets grabbing item vector
	FVector EyeVector;
	FRotator EyeRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(EyeVector, EyeRotator);

	FVector LineTrace = EyeVector + EyeRotator.Vector() * Reach;

	// Gets grabing item ID
	FHitResult Hit = GetFirstPhisycsBodyInReach();
	AActor* ActorHit = Hit.GetActor();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();

	// Grab the item you know the ID before (59)
	if (ActorHit && ActorHit->GetName().Left(8)!="BP_Block")
	{
		if (haveItem)
		{
			Server_SpawnObject(1, ItemID, LineTrace, EyeRotator);
			ABrokenBlockRef = Cast<ABrokenBlock>(ActorHit);
			if (ABrokenBlockRef)
				ItemID = ABrokenBlockRef->GetMesh();
			Server_Destroy(ActorHit);
			BaseCharacterRef->AddToGUI(ItemID);
		}
		else
		{
			ABrokenBlockRef = Cast<ABrokenBlock>(ActorHit);
			if (ABrokenBlockRef)
				ItemID = ABrokenBlockRef->GetMesh();
			//UE_LOG(LogTemp, Warning, TEXT("You Hit %i"), ItemID );
			haveItem = 1;
			Server_Destroy(ActorHit);
			BaseCharacterRef->AddToGUI(ItemID);
		}
	}

}

//Gets first item in reach name
FHitResult UPicker::GetFirstPhisycsBodyInReach() const
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


//Release item
void UPicker::Release()
{
	if (haveItem)
	{
		FVector EyeVector;
		FRotator EyeRotator;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(EyeVector, EyeRotator);
		FVector SpawnVector = EyeVector + EyeRotator.Vector() * Reach;
		Server_SpawnObject(1, ItemID, SpawnVector, EyeRotator);
		haveItem = 0;
		BaseCharacterRef->AddToGUI(0);
	}
}
void UPicker::Place()
{
	if (haveItem)
	{
		FVector EyeVector;
		FRotator EyeRotator;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(EyeVector, EyeRotator);
		FVector SpawnVector = EyeVector + EyeRotator.Vector() * Reach;
		SpawnVector /= 100.f;
		SpawnVector.X = floor(SpawnVector.X);
		SpawnVector.Y = floor(SpawnVector.Y);
		SpawnVector.Z = floor(SpawnVector.Z);
		SpawnVector *= 100.f;
		SpawnVector.X += 50.f;
		SpawnVector.Y += 50.f;
		SpawnVector.Z += 50.f;
		FRotator SpawnRotator = { 0.f,0.f,0.f };
		Server_SpawnObject(0, ItemID, SpawnVector, SpawnRotator);
		haveItem = 0;
		BaseCharacterRef->AddToGUI(0);
	}
}


void UPicker::Server_SpawnObject_Implementation(bool type, int32 ID, FVector Loc, FRotator Rot)
{
	FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor<BP_AIPawnNPC>(this->GetClass(), SpawnVector, SpawnRotation, SpawnInfo)
	TMPAActor = GetWorld()->SpawnActor<AActor>(BaseCharacterRef->GetActorType(type), Loc, Rot, SpawnInfo);
	if (type == 0)
	{
		ABlockRef = Cast<ABlock>(TMPAActor);
		if (ABlockRef)
			ABlockRef->SetMesh(ID);
	}
	else if (type == 1)
	{
		ABrokenBlockRef = Cast<ABrokenBlock>(TMPAActor);
		if (ABrokenBlockRef)
			ABrokenBlockRef->SetMesh(ID);
	}
}

void UPicker::Server_Destroy_Implementation(AActor* ActorToDestroy)
{
	ActorToDestroy->Destroy();
}