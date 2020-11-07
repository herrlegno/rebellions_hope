// Herrlegno


#include "RebellionsHopePlayerController.h"

#include "Kismet/GameplayStatics.h"

void ARebellionsHopePlayerController::BeginPlay() {
	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MainCameraTag, Cameras);
	if(Cameras.Num() > 0) SetViewTarget(Cameras[0]);
}
