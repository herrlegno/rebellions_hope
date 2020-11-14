// Herrlegno

#include "InvaderMovementComponent.h"
#include "RebellionsHopeEnemy.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values for this component's properties
UInvaderMovementComponent::UInvaderMovementComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UInvaderMovementComponent::ChangeMovement(EInvaderMovementType NewMovement) {
	if(NewMovement == EInvaderMovementType::Forward) {
		LastCollision = Movement;
		ForwardMovementStartLocation = GetOwner()->GetActorLocation();
	}
	Movement = NewMovement;
}

// Called when the game starts
void UInvaderMovementComponent::BeginPlay() {
	Super::BeginPlay();
	// ...
}

// Called every frame
void UInvaderMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Owner = GetOwner();
	if (!Owner)
		return;
	switch (Movement) {
	case EInvaderMovementType::Right: {
		MoveRight(Velocity * DeltaTime);
		break;
	}
	case EInvaderMovementType::Left: {
		MoveRight(-Velocity * DeltaTime);
		break;
	}
	case EInvaderMovementType::Forward: {
		if(FGenericPlatformMath::Abs(Owner->GetActorLocation().X - ForwardMovementStartLocation.X) >= StepDistance) {
			if(LastCollision == EInvaderMovementType::Left) ChangeMovement(EInvaderMovementType::Right);
			if(LastCollision == EInvaderMovementType::Right) ChangeMovement(EInvaderMovementType::Left);
			break;
		}
		MoveForward(Velocity * DeltaTime);
		break;
	}
	}
}

void UInvaderMovementComponent::MoveRight(const float DeltaVelocity) const {
	AActor* Owner =  GetOwner();
	const FVector CurrentLocation = Owner->GetActorLocation();
	const FVector RightVector = Owner->GetActorRightVector();
	Owner->SetActorLocation(CurrentLocation + (RightVector * DeltaVelocity));
}

void UInvaderMovementComponent::MoveForward(const float DeltaVelocity) const {
	AActor* Owner =  GetOwner();
	const FVector CurrentLocation = Owner->GetActorLocation();
	const FVector ForwardVector = Owner->GetActorForwardVector();
	Owner->SetActorLocation(CurrentLocation + (ForwardVector * DeltaVelocity));
}
