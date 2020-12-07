// Herrlegno

#include "RebellionsHopeEnemy.h"
#include "FireComponent.h"
#include "InvaderMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RebellionsHope/RebellionsHopeGameModeBase.h"

// Sets default values
ARebellionsHopeEnemy::ARebellionsHopeEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	FireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
	MovementComponent = CreateDefaultSubobject<UInvaderMovementComponent>(TEXT("MovementComponent"));
	CreateHierarchy();
	SetMesh();
	SetGizmos();
	SetComponents();
}

// Called when the game starts or when spawned
void ARebellionsHopeEnemy::BeginPlay() {
	Super::BeginPlay();
	Active = true;
}

// Called every frame
void ARebellionsHopeEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ARebellionsHopeEnemy::Fire() {
	if (!FireComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s: FireComponent not found!"), *GetFName().ToString());
		return;
	}
	if (Active)
		FireComponent->Fire();
}

void ARebellionsHopeEnemy::Deactivate() {
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	Active = false;
}

void ARebellionsHopeEnemy::CreateHierarchy() {
	RootComponent = Root;
	Mesh->AttachToComponent(Root,
	                        FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	HitBox->AttachToComponent(Root,
	                          FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
}

void ARebellionsHopeEnemy::SetMesh() const {
	UStaticMesh* SelectedMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(DefaultStaticMeshPath).Object;
	Mesh->SetStaticMesh(SelectedMesh);
	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	Mesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

void ARebellionsHopeEnemy::SetGizmos() const {
	ForwardArrow->SetHiddenInGame(true);
	ForwardArrow->AttachToComponent(RootComponent,
	                                FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
}

void ARebellionsHopeEnemy::SetComponents() {
	AddOwnedComponent(FireComponent);
	AddOwnedComponent(MovementComponent);
}

void ARebellionsHopeEnemy::NotifyActorBeginOverlap(AActor* OtherActor) {
	auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (OtherActor->ActorHasTag(FName("EndGame"))) {
		GameMode->EndGameDelegate.ExecuteIfBound();
	}
	if (OtherActor->ActorHasTag(FName("SideLimit"))) {
		Spawner->NotifyCollision();
		return;
	}
	if (OtherActor->IsA(ABullet::StaticClass())) {
		ABullet* Bullet = Cast<ABullet>(OtherActor);
		if (Bullet->BulletType != EBulletType::PlayerBullet)
			return;
		GameMode->InvaderDestroyed.Broadcast();
		Bullet->Destroy();
		Deactivate();
	}
}

void ARebellionsHopeEnemy::Activate() {
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	Active = true;
}
