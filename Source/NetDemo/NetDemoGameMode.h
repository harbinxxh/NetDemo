// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "NetDemoGameMode.generated.h"

UCLASS(minimalapi)
class ANetDemoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ANetDemoGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetDecacyRate();

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWinMutiplier();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power")
	float PowerDrainDelay;

	FTimerHandle PowerDrainTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWinMutiplier;

	//人物角色电量流失率(初始电量的%)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float DecayRate;

	int32 DeadPlayerCount;

private:
	void DrainPowerOverTime();

};



