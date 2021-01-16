// Herrlegno

#include "RebellionsHopePlayerPawn.h"
#include "FireComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "RebellionsHope/RebellionsHopeGameModeBase.h"
#include "Sound/SoundCue.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ARebellionsHopePlayerPawn::ARebellionsHopePlayerPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Component creation
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	FireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
	SetMesh();
	SetGizmos();
	SetComponents();
}

float ARebellionsHopePlayerPawn::GetHealth() const { return Health; }

int32 ARebellionsHopePlayerPawn::GetPoints() const { return Points; }

// Called when the game starts or when spawned
void ARebellionsHopePlayerPawn::BeginPlay() {
	Super::BeginPlay();
	DefaultRotation = GetMeshComponent()->GetRelativeRotation();
	Health = MaxHealth;
	const auto World = GetWorld();
	auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(World));
	GameMode->InvaderDestroyed.AddUObject(this, &ARebellionsHopePlayerPawn::OnInvaderDestroyed);
	GameMode->SquadDissolved.BindUObject(this, &ARebellionsHopePlayerPawn::OnSquadDissolved);
	GetFloatingPawnMovement()->MaxSpeed = Speed;
}

// Called every frame
void ARebellionsHopePlayerPawn::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Dashing) Dash(DeltaTime);
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
	MovementComponent = FindComponentByClass<UFloatingPawnMovement>();
}

void ARebellionsHopePlayerPawn::OnMoveRight(const float Value) {
	if(this->IsHidden()) return;
	if (Dashing) return;
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
	if(this->IsHidden()) return;
	if (!FireComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s: FireComponent not found!"), *GetFName().ToString());
		return;
	}
	FireComponent->Fire();
}

void ARebellionsHopePlayerPawn::OnDash() {
	if(this->IsHidden()) return;
	const float ActualTime = GetWorld()->GetTimeSeconds();
	if (!(LastDash == 0.f || ActualTime - LastDash >= DashCooldown)) return;
	Dashing = true;
	LastDash = ActualTime;
	DashStart = GetActorLocation();
	GetFloatingPawnMovement()->MaxSpeed = DashSpeed;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DashParticles, GetActorLocation(),
                                                     FQuat::Identity.Rotator(), FVector(.5f));
}

void ARebellionsHopePlayerPawn::RotateTo(const FRotator& TargetRotation) const {
	const FRotator CurrentRotation = GetMeshComponent()->GetRelativeRotation();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const float InterpolationSpeed = 5 * DeltaTime;
	GetMeshComponent()->SetRelativeRotation(FMath::Lerp(CurrentRotation,
	                                                    TargetRotation,
	                                                    InterpolationSpeed));
}

void ARebellionsHopePlayerPawn::OnInvaderDestroyed(int32 index) {
	const auto World = GetWorld();
	auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(World));
	Points += GameMode->PointsPerInvader;
}

void ARebellionsHopePlayerPawn::OnSquadDissolved() {
	const auto World = GetWorld();
	auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(World));
	Points += GameMode->PointsPerSquad;
}

void ARebellionsHopePlayerPawn::Dash(const float DeltaTime) {
	const auto Distance = FVector::Distance(DashStart, GetActorLocation());
	if (Distance >= DashDistance) {
		Dashing = false;
		GetFloatingPawnMovement()->MaxSpeed = Speed;
		return;
	}
	const FVector RightVector = GetActorRightVector();
	const int Direction = Right ? 1 : -1;
	AddMovementInput(RightVector, DashSpeed * Direction * DeltaTime);
	RotateTo(DefaultRotation + MovementRotation * Direction);
}

void ARebellionsHopePlayerPawn::NotifyGameOver() const {
	const auto World = GetWorld();
	auto GameMode = Cast<ARebellionsHopeGameModeBase>(UGameplayStatics::GetGameMode(World));
	GameMode->EndGameDelegate.ExecuteIfBound();
}

UFloatingPawnMovement* ARebellionsHopePlayerPawn::GetFloatingPawnMovement() const {
	return Cast<UFloatingPawnMovement>(MovementComponent);
}

void ARebellionsHopePlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor) {
	if (OtherActor->IsA(ABullet::StaticClass())) {
		ABullet* bullet = Cast<ABullet>(OtherActor);
		if (bullet->BulletType == EBulletType::EnemyBullet) {
			Health = FMath::Clamp<float>(Health - (MaxHealth / 3.f), 0, 100);
			if (Health <= 0) {
				SetActorHiddenInGame(true);
				SetActorEnableCollision(false);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionCue, GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, GetActorLocation(),
                                                     FQuat::Identity.Rotator(), FVector(.5f));
				NotifyGameOver();
			} else {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(),
                                                     FQuat::Identity.Rotator(), FVector(.5f));
			}
			bullet->Destroy();
		}
	}
}

void ARebellionsHopePlayerPawn::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                          bool bSelfMoved, FVector HitLocation, FVector HitNormal,
                                          FVector NormalImpulse, const FHitResult& Hit) {
	if (Other->ActorHasTag(FName("SideLimit"))) { Dashing = false; }
}

