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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power")
	float PowerDrainDelay;

	FTimerHandle PowerDrainTimer;

	//�����ɫ������ʧ��(��ʼ������%)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float DecayRate;

private:
	void DrainPowerOverTime();

};



