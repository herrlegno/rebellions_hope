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
	UPROPERTY()
	class UInvaderMovementComponent* MovementComponent = nullptr;

	UPROPERTY()
	ASquadSpawner* Spawner = nullptr;

	// Sets default values for this actor's properties
	ARebellionsHopeEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static constexpr const TCHAR* DefaultStaticMeshPath = TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'");

	UPROPERTY()
	class USceneComponent* Root = nullptr;

	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* HitBox = nullptr;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UFireComponent* FireComponent = nullptr;

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void CreateHierarchy();
	void SetMesh() const;
	void SetGizmos() const;
	void SetComponents();
};
