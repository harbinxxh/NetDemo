// Fill out your copyright notice in the Description page of Project Settings.

#include "NetDemo.h"
#include "BatteryPickup.h"
#include "Net/UnrealNetwork.h"



ABatteryPickup::ABatteryPickup()
{

	bReplicateMovement = true;

	// ��������Ч��
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	// ���п��ƶ���
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	BattaryPower = 200.f;
}

void ABatteryPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABatteryPickup, BattaryPower);
}

void ABatteryPickup::PickedUpBy(APawn* Pawn)
{
	Super::PickedUpBy(Pawn);
	if (Role == ROLE_Authority)
	{
		SetLifeSpan(2.f);//2��֮���Զ�����
	}
}

float ABatteryPickup::GetPower()
{
	return BattaryPower;
}
