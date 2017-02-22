// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "NetDemo.h"
#include "NetDemoGameMode.h"
#include "NetDemoCharacter.h"
#include "NetDemoGameState.h"

ANetDemoGameMode::ANetDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/Blueprint/BP_NetDemoHUD"));
	if (PlayerHUDBPClass.Class != NULL)
	{
		HUDClass = PlayerHUDBPClass.Class;
	}

	GameStateClass = ANetDemoGameState::StaticClass();

	DecayRate = 0.05f;
	PowerDrainDelay = 0.25f;
	PowerToWinMutiplier = 1.2f;
	DeadPlayerCount = 0;
}

void ANetDemoGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(PowerDrainTimer, this, &ANetDemoGameMode::DrainPowerOverTime, PowerDrainDelay, true);

	UWorld* World = GetWorld();
	check(World);

	ANetDemoGameState* MyGameState = Cast<ANetDemoGameState>(GameState);
	check(MyGameState);

	DeadPlayerCount = 0;

	MyGameState->SetCurrentState(EBatteryPlayState::EPlaying);

	for (FConstControllerIterator It = World->GetControllerIterator(); It; It++)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (ANetDemoCharacter* TestCharacter = Cast<ANetDemoCharacter>(PlayerController->GetPawn()))
			{
				MyGameState->PowerToWin = TestCharacter->GetInitalPower() * PowerToWinMutiplier;
				break;
			}
		}
	}

}

float ANetDemoGameMode::GetDecacyRate()
{
	return DecayRate;
}

float ANetDemoGameMode::GetPowerToWinMutiplier()
{
	return PowerToWinMutiplier;
}

void ANetDemoGameMode::DrainPowerOverTime()
{
	UWorld* World = GetWorld();
	check(World);

	ANetDemoGameState* MyGameState = Cast<ANetDemoGameState>(GameState);
	check(MyGameState);

	for (FConstControllerIterator It = World->GetControllerIterator(); It; It++)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (ANetDemoCharacter* TestCharacter = Cast<ANetDemoCharacter>(PlayerController->GetPawn()))
			{
				if (TestCharacter->GetCurrentPower() > MyGameState->PowerToWin)
				{
					MyGameState->SetCurrentState(EBatteryPlayState::EWon);
				}
				else if (TestCharacter->GetCurrentPower() > 0)
				{
					TestCharacter->UpdatePower(-PowerDrainDelay*DecayRate*TestCharacter->GetInitalPower());
				}
				else
				{
					//Player Over
					TestCharacter->DetachFromControllerPendingDestroy();
					DeadPlayerCount += 1;

					// Game Over
					if (DeadPlayerCount >= GetNumPlayers())
					{
						MyGameState->SetCurrentState(EBatteryPlayState::EGameOver);
					}
				}
			}
		}
	}



}
