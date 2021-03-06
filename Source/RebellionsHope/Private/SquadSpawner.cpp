// Herrlegno

#include "SquadSpawner.h"
#include "RebellionsHopeEnemy.h"
#include "InvaderMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RebellionsHope/RebellionsHopeGameModeBase.h"

// Sets default values
ASquadSpawner::ASquadSpawner() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DebugMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugMesh"));
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	RootComponent = Root;
	SetGizmos();
	SetDebugMesh();
}

void ASquadSpawner::NotifyCollision() {
	for (auto& Invader : SquadMembers) {
		if (Invader != nullptr)
			Invader->MovementComponent->ChangeMovement(EInvaderMovementType::Forward);
	}
}

// Called when the game starts or when spawned
void ASquadSpawner::BeginPlay() {
	Super::BeginPlay();
	SetupEnemyTemplate();
	SpawnSquad();
	auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->InvaderDestroyed.AddUObject(this, &ASquadSpawner::OnInvaderDestroyed);
}

// Called every frame
void ASquadSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	RandomFire();
}

void ASquadSpawner::SetGizmos() const {
	ForwardArrow->SetHiddenInGame(true);
	ForwardArrow->AttachToComponent(RootComponent,
	                                FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
}

void ASquadSpawner::SetDebugMesh() const {
	UStaticMesh* SelectedMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(DebugStaticMeshPath).Object;
	DebugMesh->SetStaticMesh(SelectedMesh);
	DebugMesh->SetRelativeScale3D(FVector(30.f, 30.f, 30.f));
	DebugMesh->AttachToComponent(Root,
	                             FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	DebugMesh->SetHiddenInGame(true);
}

void ASquadSpawner::SetupEnemyTemplate() {
	if (EnemyClass->IsChildOf<ARebellionsHopeEnemy>())
		EnemyTemplate = NewObject<ARebellionsHopeEnemy>(this, EnemyClass->GetFName(), RF_NoFlags,
		                                                EnemyClass.GetDefaultObject());
	else
		EnemyTemplate = NewObject<ARebellionsHopeEnemy>();
	EnemyTemplate->Spawner = this;
	EnemyTemplate->MovementComponent->Velocity = InvaderVelocity;
}

void ASquadSpawner::SpawnSquad() {
	const FTransform OriginTransform = GetActorTransform();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Template = EnemyTemplate;
	int Index = 0;
	const int HalfRow = FMath::RoundToInt(RowSize / 2);
	const int HalfColumn = FMath::RoundToInt(ColumnSize / 2);
	const bool EvenRow = RowSize % 2 == 0;
	const bool EvenColumn = ColumnSize % 2 == 0;
	for (int i = -HalfRow; i < RowSize - HalfRow; i++) {
		for (int j = -HalfColumn; j < ColumnSize - HalfColumn; j++) {
			const FTransform LocalTransform(FVector(i * Separation + (EvenRow ? Separation / 2 : 0),
			                                        j * Separation + (EvenColumn ? Separation / 2 : 0), 0.f));
			const FTransform SpawnTransform = LocalTransform * OriginTransform;
			ARebellionsHopeEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ARebellionsHopeEnemy>(
				SpawnTransform.GetLocation(), SpawnTransform.Rotator(), SpawnParameters);
			SpawnedEnemy->Index = Index;
			SquadMembers.Emplace(SpawnedEnemy);
			Index++;
		}
	}
	InvadersAlive = RowSize * ColumnSize;
}

void ASquadSpawner::RandomFire() {
	if (FMath::RandRange(0.f, 1.f) <= FirePercentage / 100) {
		const int RandomIndex = FMath::RandRange(0, SquadMembers.Num() - 1);
		const auto Invader = SquadMembers[RandomIndex];
		if (Invader != nullptr)
			Invader->Fire();
	}
}

void ASquadSpawner::OnInvaderDestroyed(int Index) {
	InvadersAlive--;
	SquadMembers[Index] = nullptr;
	if (InvadersAlive <= 0) {
		const auto World = GetWorld();
		auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(World));
		GameMode->SquadDissolved.ExecuteIfBound();
		SpawnSquad();
	}
}
