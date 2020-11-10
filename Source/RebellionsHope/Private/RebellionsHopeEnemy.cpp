// Herrlegno

#include "RebellionsHopeEnemy.h"

#include "FireComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ARebellionsHopeEnemy::ARebellionsHopeEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	FireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
	CreateHierarchy();
	SetMesh();
	SetGizmos();
	SetComponents();
}

// Called when the game starts or when spawned
void ARebellionsHopeEnemy::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ARebellionsHopeEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FireComponent->Fire();
}

void ARebellionsHopeEnemy::CreateHierarchy() {
	RootComponent = Root;
	Mesh->AttachToComponent(Root,
	                        FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	HitBox->AttachToComponent(Mesh,
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
}