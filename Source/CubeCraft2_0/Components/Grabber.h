#pragma once
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class ABrokenBlock;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CUBECRAFT2_0_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
		bool IsSetGrabber = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float Reach = 200.f;

	UPROPERTY(EditAnywhere)
		bool DebugLine = 0;

	AActor* ActorHit;

	UPROPERTY()
		UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
		UInputComponent* InputComponent = nullptr;

	ABrokenBlock* BrokenBLockRef;

	UFUNCTION(BlueprintCallable)
	void SetUpInputComponent();
	UFUNCTION(BlueprintCallable)
	void FindPhysicsHandle();
	void Grab();
	void Release();

	FHitResult GetFirstPhisycsBodyInReach() const;

};