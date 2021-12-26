// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "../GameMode/CubeCraftPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);

	bReplicates = true;
}


void ABaseCharacter::IsMenuActive()
{
	if (!IsMenu)
	{
		ActiveMenu(1);
		IsMenu=1;
	}
	else
	{
		ActiveMenu(0);
		IsMenu = 0;
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<ACubeCraftPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ABaseCharacter::SprintOn);
	//PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ABaseCharacter::SprintOff);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ABaseCharacter::LookUpPad);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ABaseCharacter::LookAroundPad);
	PlayerInputComponent->BindAction(TEXT("Menu"), EInputEvent::IE_Pressed, this, &ABaseCharacter::IsMenuActive);
	ConfigurateBlueprints();
}

void ABaseCharacter::ActiveMenu(bool bIsMenuActive)
{
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(bIsMenuActive);
	}
	bActiveMenu(bIsMenuActive);
}
void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * Speed);
}
void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * Speed);
}

void ABaseCharacter::LookUpPad(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookAroundPad(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}




