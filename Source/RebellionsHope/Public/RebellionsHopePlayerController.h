// Herrlegno

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RebellionsHopePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class REBELLIONSHOPE_API ARebellionsHopePlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	private:
	FName MainCameraTag = "MainCamera";
};
