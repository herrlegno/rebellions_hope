// Herrlegno

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/DefaultPawn.h"
#include "Bullet.h"
#include "RebellionsHopePlayerPawn.generated.h"

UCLASS()
class REBELLIONSHOPE_API ARebellionsHopePlayerPawn : public ADefaultPawn {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0", ClampMax = "100"))
	int32 MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0"))
	float Speed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0"))
	float DashCooldown = 5.f;

	// Sets default values for this pawn's properties
	ARebellionsHopePlayerPawn();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPoints() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Player")
	class UParticleSystem* HitEmitter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static constexpr const TCHAR* DefaultStaticMeshPath = TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'");
	int32 Points = 0;

	float Health;
	bool Right = true;
	float LastDash = 0.f;
	FRotator DefaultRotation;

	UPROPERTY(EditAnywhere, Category = "Player")
	FRotator MovementRotation = FRotator(45.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UFireComponent* FireComponent = nullptr;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	void SetMesh() const;
	void SetGizmos() const;
	void SetComponents();
	virtual void OnMoveRight(float Value);
	void OnFire();
	void OnDash();
	void RotateTo(const FRotator& TargetRotation) const;
	void OnInvaderDestroyed(int32 index);
	void OnSquadDissolved();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
