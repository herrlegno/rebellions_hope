// Copyright Epic Games, Inc. All Rights Reserved.


#include "RebellionsHopeGameModeBase.h"

#include "Public/RebellionsHopePlayerController.h"
#include "Public/RebellionsHopePlayerPawn.h"

ARebellionsHopeGameModeBase::ARebellionsHopeGameModeBase() {
	DefaultPawnClass = ARebellionsHopePlayerPawn::StaticClass();
	PlayerControllerClass = ARebellionsHopePlayerController::StaticClass();
}
