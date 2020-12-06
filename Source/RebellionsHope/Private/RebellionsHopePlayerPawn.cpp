// Herrlegno

#include "RebellionsHopePlayerPawn.h"
#include "FireComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Bullet.h"

// Sets default values
ARebellionsHopePlayerPawn::ARebellionsHopePlayerPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Component creation
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	FireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
	SetMesh();
	SetGizmos();
	SetComponents();
}

// Called when the game starts or when spawned
void ARebellionsHopePlayerPawn::BeginPlay() {
	Super::BeginPlay();
	DefaultRotation = GetMeshComponent()->GetRelativeRotation();
}

// Called every frame
void ARebellionsHopePlayerPawn::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARebellionsHopePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ARebellionsHopePlayerPawn::OnMoveRight);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ARebellionsHopePlayerPawn::OnFire);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_DoubleClick, this, &ARebellionsHopePlayerPawn::OnDash);
}

void ARebellionsHopePlayerPawn::SetMesh() const {
	UStaticMesh* DefaultMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(DefaultStaticMeshPath).Object;
	UStaticMeshComponent* Mesh = GetMeshComponent();
	USphereComponent* Collision = GetCollisionComponent();
	Mesh->SetStaticMesh(DefaultMesh);
	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	Mesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	Collision->SetSphereRadius(Mesh->Bounds.SphereRadius);
}

void ARebellionsHopePlayerPawn::SetGizmos() const {
	ForwardArrow->SetHiddenInGame(true);
	ForwardArrow->AttachToComponent(RootComponent,
	                                FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
}

void ARebellionsHopePlayerPawn::SetComponents() {
	AddOwnedComponent(FireComponent);
}

void ARebellionsHopePlayerPawn::OnMoveRight(const float Value) {
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	if (Value != 0.f) {
		Right = Value >= 0.f;
		const FVector RightVector = GetActorRightVector();
		AddMovementInput(RightVector, Speed * Value * DeltaTime);
		RotateTo(DefaultRotation + MovementRotation * (Right ? 1 : -1));
		return;
	}
	RotateTo(DefaultRotation);
}

void ARebellionsHopePlayerPawn::OnFire() {
	if (!FireComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s: FireComponent not found!"), *GetFName().ToString());
		return;
	}
	FireComponent->Fire();
}

void ARebellionsHopePlayerPawn::OnDash() {
	const float ActualTime = GetWorld()->GetTimeSeconds();
	if (LastDash == 0.f || ActualTime - LastDash >= DashCooldown) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), Right ? TEXT("Right Dash") : TEXT("Left Dash"));
		LastDash = ActualTime;
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Dash en cooldown: %f"), DashCooldown - (ActualTime - LastDash));
}

void ARebellionsHopePlayerPawn::RotateTo(const FRotator& TargetRotation) const {
	const FRotator CurrentRotation = GetMeshComponent()->GetRelativeRotation();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const float InterpolationSpeed = 5 * DeltaTime;
	GetMeshComponent()->SetRelativeRotation(FMath::Lerp(CurrentRotation,
	                                                    TargetRotation,
	                                                    InterpolationSpeed));
}

void ARebellionsHopePlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor) {
	if (OtherActor->IsA(ABullet::StaticClass())) {
		ABullet* bullet = Cast<ABullet>(OtherActor);
		if (bullet->BulletType == EBulletType::EnemyBullet) {
			UE_LOG(LogTemp, Warning, TEXT("Player has been Hit!"));
			bullet->Destroy();
		}
	}
}
