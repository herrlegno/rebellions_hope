// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquadSpawner.generated.h"

UCLASS()
class REBELLIONSHOPE_API ASquadSpawner : public AActor {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 RowSize = 5;

	UPROPERTY(EditAnywhere)
	int32 ColumnSize = 5;

	float HorizontalVelocity = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<class ARebellionsHopeEnemy> EnemyClass;

	// Sets default values for this actor's properties
	ASquadSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void NotifyCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static constexpr const TCHAR* DebugStaticMeshPath = TEXT(
		"StaticMesh'/Engine/VREditor/FloatingText/JointSphere.JointSphere'");

	UPROPERTY(EditAnywhere)
	float Separation = 200.f;

	UPROPERTY()
	class ARebellionsHopeEnemy* EnemyTemplate;

	UPROPERTY(VisibleAnywhere)
	TArray<ARebellionsHopeEnemy*> SquadMembers;

	UPROPERTY()
	class USceneComponent* Root = nullptr;

	UPROPERTY()
	class UStaticMeshComponent* DebugMesh = nullptr;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	void SetGizmos() const;
	void SetDebugMesh() const;
	void SetupEnemyTemplate();
	void SpawnSquad();
	void RandomFire();

	float FirePercentage = 1.f;
};
