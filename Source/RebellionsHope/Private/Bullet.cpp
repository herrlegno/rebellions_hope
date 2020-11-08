// Herrlegno

#include "Bullet.h"

// Sets default values
ABullet::ABullet() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	CreateHierarchy();
	SetMesh();
}

// Called when the game starts or when spawned
void ABullet::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	const FVector Forward = GetActorForwardVector();
	Location += DeltaTime * Velocity * Forward;
	SetActorLocation(Location);
}

void ABullet::CreateHierarchy() {
	RootComponent = Root;
	Mesh->AttachToComponent(Root,
	                        FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
}

void ABullet::SetMesh() const {
	UStaticMesh* SelectedMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(DefaultStaticMeshPath).Object;
	Mesh->SetStaticMesh(SelectedMesh);
	Mesh->SetRelativeScale3D(FVector(.2f, .2f, .2f));
	Mesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}
