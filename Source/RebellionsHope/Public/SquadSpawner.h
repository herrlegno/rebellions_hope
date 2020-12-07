// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquadSpawner.generated.h"

UCLASS()
class REBELLIONSHOPE_API ASquadSpawner : public AActor {
	GENERATED_BODY()

public:
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

	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 RowSize = 5;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 ColumnSize = 5;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float InvaderVelocity = 200.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float Separation = 200.f;

	UPROPERTY(EditAnywhere, Category = "Spawner", meta =(ClampMin = "0", ClampMax = "100"))
	float FirePercentage = 1.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<class ARebellionsHopeEnemy> EnemyClass;

	UPROPERTY()
	class ARebellionsHopeEnemy* EnemyTemplate;

	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	TArray<class ARebellionsHopeEnemy*> SquadMembers;

	UPROPERTY()
	class USceneComponent* Root = nullptr;

	UPROPERTY()
	class UStaticMeshComponent* DebugMesh = nullptr;

	UPROPERTY()
	class UArrowComponent* ForwardArrow = nullptr;

	int16 InvadersAlive;

	void SetGizmos() const;
	void SetDebugMesh() const;
	void SetupEnemyTemplate();
	void SpawnSquad();
	void RandomFire();
	void OnInvaderDestroyed(int Index);
};
