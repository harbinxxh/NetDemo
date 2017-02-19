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
}
