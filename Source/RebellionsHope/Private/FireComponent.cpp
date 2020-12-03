// Herrlegno

#include "FireComponent.h"
#include "Bullet.h"

// Sets default values for this component's properties
UFireComponent::UFireComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UFireComponent::Fire() {
	if (CanShoot()) {
		SpawnBullet();
		TimeFromLastShot = GetWorld()->GetTimeSeconds();
	}
}

// Called when the game starts
void UFireComponent::BeginPlay() {
	Super::BeginPlay();
	SetupBulletTemplate();
}

// Called every frame
void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                   FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UFireComponent::SetupBulletTemplate() {
	if (BulletClass->IsChildOf<ABullet>()) {
		BulletTemplate = NewObject<ABullet>(this, BulletClass->GetFName(), RF_NoFlags, BulletClass.GetDefaultObject());
		return;
	}
	BulletTemplate = NewObject<ABullet>();
}

void UFireComponent::SpawnBullet() const {
	if (BulletTemplate) {
		const AActor* Owner = GetOwner();
		const FVector SpawnLocation = Owner->GetActorLocation();
		const FRotator SpawnRotation = Owner->GetActorRotation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Template = BulletTemplate;
		BulletTemplate->SetActorEnableCollision(true);
		BulletTemplate->BulletType = BulletType;
		GetWorld()->SpawnActor<ABullet>(SpawnLocation, SpawnRotation, SpawnParameters);
	}
}

bool UFireComponent::CanShoot() const {
	const float ActualTime = GetWorld()->GetTimeSeconds();
	return ActualTime - TimeFromLastShot > 60 / FireRate;
}
