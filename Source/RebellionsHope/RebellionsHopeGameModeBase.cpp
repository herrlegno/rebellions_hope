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
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARebellionsHopeGameModeBase::OpenMenu, 2.f, false);
}

void ARebellionsHopeGameModeBase::OpenMenu() const {
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}
