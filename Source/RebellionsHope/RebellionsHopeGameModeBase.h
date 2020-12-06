// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RebellionsHopeGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FMulticastDelegateSignature);
DECLARE_DELEGATE(FStandardDelegateSignature);

UCLASS()
class REBELLIONSHOPE_API ARebellionsHopeGameModeBase : public AGameModeBase {
	GENERATED_BODY()
	ARebellionsHopeGameModeBase();

public:
	FStandardDelegateSignature EndGameDelegate;
	FMulticastDelegateSignature InvaderDestroyed;

	UPROPERTY(BlueprintReadWrite)
	int32 PointsPerInvader = 1000.f;

	void OnEndGame() const;
};
