// Herrlegno

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/DefaultPawn.h"
#include "RebellionsHopePlayerPawn.generated.h"

UCLASS()
class REBELLIONSHOPE_API ARebellionsHopePlayerPawn : public ADefaultPawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARebellionsHopePlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0"))
	float Speed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0"))
	float DashCooldown = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin= "0"))
	float FireRate = 100.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static constexpr const TCHAR* DefaultStaticMeshPath = TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'");
	bool Right = true;
	float LastDash = 0.f;
	FRotator DefaultRotation;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	UPROPERTY(EditAnywhere)
	class UFireComponent* FireComponent = nullptr;

	UPROPERTY(EditAnywhere)
	FRotator MovementRotation = FRotator(45.f, 0.f, 0.f);

	void SetMesh() const;
	void SetGizmos() const;
	void SetComponents();
	virtual void OnMoveRight(float Value) override;
	void OnFire();
	void OnDash();
	void RotateTo(const FRotator& TargetRotation) const;

};
