// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class NETDEMO_API APickup : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	APickup();
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool b);

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void WasCollected();
	virtual void WasCollected_Implementation();

	UFUNCTION(BlueprintAuthorityOnly, Category = "Pickup")
	virtual void PickedUpBy(APawn* Pawn);

protected:
	// Property is relevant to network replication. Notify actors when a property is replicated (usage: ReplicatedUsing=FunctionName).
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive; // 是否激活的属性

	UFUNCTION()
	virtual void OnRep_IsActive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	APawn* PickupInstigater;

private:
	UFUNCTION(NetMulticast, Unreliable)
	void ClientOnPickedUpBy(APawn* Pawn);

};
