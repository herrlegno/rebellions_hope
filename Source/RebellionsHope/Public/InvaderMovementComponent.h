// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvaderMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EInvaderMovementType: uint8 {
	// Stop UMETA(DisplayName = "Stopped"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Forward UMETA(DisplayName = "Forward"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REBELLIONSHOPE_API UInvaderMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvaderMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInvaderMovementType Movement = EInvaderMovementType::Right;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float Velocity = 100.f;

	UPROPERTY(EditAnywhere)
	float StepDistance = 100.f;

	float StepProgress = 0.f;
	
	EInvaderMovementType LastCollision;

	void MoveRight(const float DeltaVelocity) const;
	void MoveForward(const float DeltaVelocity) const;
};
