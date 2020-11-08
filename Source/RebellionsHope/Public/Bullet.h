// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class REBELLIONSHOPE_API ABullet : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Properties", meta=(ClampMin = "0"))
	float Velocity = 1000.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static constexpr const TCHAR* DefaultStaticMeshPath = TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'");

	UPROPERTY()
	class USceneComponent* Root = nullptr;

	void CreateHierarchy();
	void SetMesh() const;
};
