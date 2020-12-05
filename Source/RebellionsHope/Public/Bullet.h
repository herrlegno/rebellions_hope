// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UENUM(BlueprintType)
enum class EBulletType: uint8 {
	EnemyBullet UMETA(DisplayName = "Enemy"),
	PlayerBullet UMETA(DisplayName = "Player"),
};

UCLASS()
class REBELLIONSHOPE_API ABullet : public AActor {
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Properties", meta=(ClampMin = "0"))
	float Velocity = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	EBulletType BulletType;

	// Sets default values for this actor's properties
	ABullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static constexpr const TCHAR* DefaultStaticMeshPath = TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'");

	UPROPERTY()
	class USceneComponent* Root = nullptr;

	void CreateHierarchy();
	void SetMesh() const;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
