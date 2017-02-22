// Fill out your copyright notice in the Description page of Project Settings.

#include "NetDemo.h"
#include "NetDemoGameState.h"
#include "Net/UnrealNetwork.h"



ANetDemoGameState::ANetDemoGameState()
{
	CurrentState = EBatteryPlayState::EUnknown;
}

void ANetDemoGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetDemoGameState, PowerToWin);
	DOREPLIFETIME(ANetDemoGameState, CurrentState);
}

EBatteryPlayState ANetDemoGameState::GetCurrentState() const
{
	return CurrentState;
}

void ANetDemoGameState::SetCurrentState(EBatteryPlayState State)
{
	CurrentState = State;
}

void ANetDemoGameState::OnRep_CurrentState()
{
	//
}
