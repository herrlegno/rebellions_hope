// Copyright Epic Games, Inc. All Rights Reserved.

#include "RebellionsHopeGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Public/RebellionsHopePlayerController.h"
#include "Public/RebellionsHopePlayerPawn.h"

ARebellionsHopeGameModeBase::ARebellionsHopeGameModeBase() {
	DefaultPawnClass = ARebellionsHopePlayerPawn::StaticClass();
	PlayerControllerClass = ARebellionsHopePlayerController::StaticClass();
	EndGameDelegate.BindUObject(this, &ARebellionsHopeGameModeBase::OnEndGame);
}

void ARebellionsHopeGameModeBase::OnEndGame() const {
	UGameplayStatics::OpenLevel(this, FName("Level_1"));
}
