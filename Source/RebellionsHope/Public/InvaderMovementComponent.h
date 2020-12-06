// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvaderMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EInvaderMovementType: uint8 {
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Forward UMETA(DisplayName = "Forward"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REBELLIONSHOPE_API UInvaderMovementComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity = 200.f;

	UPROPERTY(EditAnywhere)
	float StepDistance = 100.f;

	// Sets default values for this component's properties
	UInvaderMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeMovement(EInvaderMovementType NewMovement);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	EInvaderMovementType LastCollision;
	FVector ForwardMovementStartLocation;
	FRotator DefaultRotation;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	EInvaderMovementType Movement = EInvaderMovementType::Right;

	UPROPERTY(EditAnywhere)
	FRotator MovementRotation = FRotator(45.f, 0.f, 0.f);

	void MoveRight(float DeltaVelocity) const;
	void MoveForward(float DeltaVelocity) const;
	void RotateTo(const FRotator& TargetRotation) const;
};
