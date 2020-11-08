// Herrlegno

#include "SquadSpawner.h"
#include "RebellionsHopeEnemy.h"
#include "Components/ArrowComponent.h"

// Sets default values
ASquadSpawner::ASquadSpawner() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	RootComponent = Root;
	SetGizmos();
}

// Called when the game starts or when spawned
void ASquadSpawner::BeginPlay() {
	Super::BeginPlay();
	SetupEnemyTemplate();
	SpawnSquad();
}

// Called every frame
void ASquadSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ASquadSpawner::SetGizmos() {
	ForwardArrow->SetHiddenInGame(true);
	ForwardArrow->AttachToComponent(RootComponent,
	                                FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
}

void ASquadSpawner::SetupEnemyTemplate() {
	if (EnemyClass->IsChildOf<ARebellionsHopeEnemy>()) {
		EnemyTemplate = NewObject<ARebellionsHopeEnemy>(this, EnemyClass->GetFName(), RF_NoFlags,
		                                                EnemyClass.GetDefaultObject());
		return;
	}
	EnemyTemplate = NewObject<ARebellionsHopeEnemy>();
}

// TODO: FIX LOCATION SHOULD = ROOT PLANE
void ASquadSpawner::SpawnSquad() {
	const FVector OriginLocation = RootComponent->GetComponentLocation();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Template = EnemyTemplate;
	for (int i = 0; i < RowSize; i++) {
		for (int j = 0; j < ColumnSize; j++) {
			FVector SpawnLocation = OriginLocation + FVector(i * Separation, j * Separation, 0.f);
			ARebellionsHopeEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ARebellionsHopeEnemy>(
				SpawnLocation, FRotator(0.f, 0.f, 0.f), SpawnParameters);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnedEnemy->GetActorRotation().ToString());
			SquadMembers.Emplace(SpawnedEnemy);
		}
	}
}
