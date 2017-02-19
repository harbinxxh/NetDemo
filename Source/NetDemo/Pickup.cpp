// Fill out your copyright notice in the Description page of Project Settings.

#include "NetDemo.h"
#include "Net/UnrealNetwork.h"
#include "Pickup.h"




APickup::APickup()
{
	// If true, this actor will replicate to remote machines
	bReplicates = true;

	// If false, this tick function will never be registered and will never tick. Only settable in defaults.
	PrimaryActorTick.bCanEverTick = false;

	GetStaticMeshComponent()->bGenerateOverlapEvents = true;

	if (Role = ROLE_Authority)
	{
		bIsActive = true;
	}

}

void APickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickup, bIsActive);

}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool b)
{
	if (Role == ROLE_Authority)
	{
		bIsActive = b;
	}
}

void APickup::WasCollected_Implementation()
{
	UE_LOG(LogClass, Log, TEXT("APickup::WasCollected_Implementation %s"), *GetName());
}

void APickup::PickedUpBy(APawn* Pawn)
{
	if (Role == ROLE_Authority)
	{
		PickupInstigater = Pawn;
		ClientOnPickedUpBy(Pawn);
	}
}

void APickup::OnRep_IsActive()
{

}

void APickup::ClientOnPickedUpBy_Implementation(APawn* Pawn)
{
	PickupInstigater = Pawn;
	WasCollected();
}
