// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "NetDemo.h"
#include "NetDemoGameMode.h"
#include "NetDemoCharacter.h"

ANetDemoGameMode::ANetDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	DecayRate = 0.05f;
	PowerDrainDelay = 0.25f;
}

void ANetDemoGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(PowerDrainTimer, this, &ANetDemoGameMode::DrainPowerOverTime, PowerDrainDelay, true);
}

float ANetDemoGameMode::GetDecacyRate()
{
	return DecayRate;
}

void ANetDemoGameMode::DrainPowerOverTime()
{
	UWorld* World = GetWorld();
	check(World);
	for (FConstControllerIterator It = World->GetControllerIterator(); It; It++)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (ANetDemoCharacter* TestCharacter = Cast<ANetDemoCharacter>(PlayerController->GetPawn()))
			{
				TestCharacter->UpdatePower(-PowerDrainDelay*DecayRate*TestCharacter->GetInitalPower());
			}
		}
	}



}
