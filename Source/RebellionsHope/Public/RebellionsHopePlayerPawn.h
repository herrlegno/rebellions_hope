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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	static constexpr const TCHAR* defaultStaticMeshPath = TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'");
	
	UPROPERTY(EditAnywhere, Category = "Player", meta = (ClampMin = "0"))
	float Speed = 100.f;
	UPROPERTY(EditAnywhere, Category="Player", meta = (ClampMin="0"))
	float DashCooldown = 5.f;

	bool Right = true;
	float LastDash = 0.f;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	void SetMesh() const;
	void SetGizmos() const;
	virtual void OnMoveRight(float Value) override;
	void OnFire();
	void OnDash();
};
