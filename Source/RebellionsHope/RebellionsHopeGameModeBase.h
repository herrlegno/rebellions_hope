// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RebellionsHopeGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateSignatureOneParam, int);
DECLARE_DELEGATE(FStandardDelegateSignature);

UCLASS()
class REBELLIONSHOPE_API ARebellionsHopeGameModeBase : public AGameModeBase {
	GENERATED_BODY()
	ARebellionsHopeGameModeBase();

public:
	FStandardDelegateSignature EndGameDelegate;
	FMulticastDelegateSignatureOneParam InvaderDestroyed;
	FStandardDelegateSignature SquadDissolved;

	UPROPERTY(BlueprintReadWrite)
	int32 PointsPerInvader = 1000.f;

	UPROPERTY(BlueprintReadWrite)
	int32 PointsPerSquad = 500.f;

private:
	void OnEndGame() const;

	void OpenMenu() const;
};
