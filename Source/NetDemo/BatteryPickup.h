// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class NETDEMO_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	ABatteryPickup();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintAuthorityOnly, Category = "Pickup")
	virtual void PickedUpBy(APawn* Pawn) override;

	float GetPower();

protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float BattaryPower;

};
