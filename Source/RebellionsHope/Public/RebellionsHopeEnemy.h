// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "SquadSpawner.h"
#include "GameFramework/Actor.h"
#include "RebellionsHopeEnemy.generated.h"

UCLASS()
class REBELLIONSHOPE_API ARebellionsHopeEnemy : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARebellionsHopeEnemy();

	UPROPERTY()
	class UInvaderMovementComponent* MovementComponent = nullptr;

	UPROPERTY()
	ASquadSpawner* Spawner = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	static constexpr const TCHAR* DefaultStaticMeshPath = TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'");

	UPROPERTY()
	class USceneComponent* Root = nullptr;

	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY()
	class UBoxComponent* HitBox = nullptr;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	UPROPERTY()
	class UFireComponent* FireComponent = nullptr;

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void CreateHierarchy();
	void SetMesh() const;
	void SetGizmos() const;
	void SetComponents();
};
