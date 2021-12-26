#pragma once
//#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../General/BrokenBlock.h"
#include "../General/Block.h"
#include "UnrealNetwork.h"
#include "Picker.generated.h"

class ABrokenBlock;
class ABlock;
class ACubeCraftGameModeBase;
class ABaseCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CUBECRAFT2_0_API UPicker : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPicker();

	UPROPERTY(BlueprintReadOnly)
		bool IsSetPicker = 0;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float Reach = 200.f;
	
	ABlock* ABlockRef;
	ABrokenBlock* ABrokenBlockRef;
	AActor* TMPAActor;
	ACubeCraftGameModeBase* GameModeRef;
	ABaseCharacter* BaseCharacterRef;

	//UPROPERTY()
		//UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;
	

	UFUNCTION(BlueprintCallable)
	void SetUpInputComponent();
	void Pick();
	void Release();
	void Place();

	

	bool haveItem = 0;
	int32 ItemID = 0;

	FHitResult GetFirstPhisycsBodyInReach() const;

	UFUNCTION(Server, unreliable)
	void Server_SpawnObject(bool type, int32 ID, FVector Loc, FRotator Rot);
	UFUNCTION(Server, unreliable)
	void Server_Destroy(AActor* ActorToDestroy);

};

