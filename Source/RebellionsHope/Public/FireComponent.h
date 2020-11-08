// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REBELLIONSHOPE_API UFireComponent : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFireComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 100.f;

	void Fire();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ABullet* BulletTemplate;

	float TimeFromLastShot = 0.f;

	void SetupBulletTemplate();
	void SpawnBullet() const;
	bool CanShoot() const;
};
