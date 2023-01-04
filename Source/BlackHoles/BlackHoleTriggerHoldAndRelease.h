// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "BlackHoleTriggerHoldAndRelease.generated.h"

/**
 * 
 */
UCLASS()
class BLACKHOLES_API UBlackHoleTriggerHoldAndRelease : public UInputTriggerTimedBase
{
	GENERATED_BODY()

protected:

	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

public:
	// How long does the input have to be held to cause trigger?
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float HoldTimeThreshold = 0.5f;
	
};
