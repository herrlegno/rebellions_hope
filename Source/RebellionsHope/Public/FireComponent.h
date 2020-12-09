// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Bullet.h"
#include "FireComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REBELLIONSHOPE_API UFireComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	float FireRate = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBulletType BulletType;

	// Sets default values for this component's properties
	UFireComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Fire();

	UPROPERTY(EditAnywhere)
	class USoundCue* FireCue;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float TimeFromLastShot = 0.f;

	UPROPERTY()
	class ABullet* BulletTemplate;

	void SetupBulletTemplate();
	void SpawnBullet() const;
	bool CanShoot() const;
};
