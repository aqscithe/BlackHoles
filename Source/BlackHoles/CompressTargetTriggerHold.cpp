// Fill out your copyright notice in the Description page of Project Settings.


#include "CompressTargetTriggerHold.h"

ETriggerState UCompressTargetTriggerHold::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	// Update HeldDuration and derive base state
	ETriggerState State = Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);

	// Trigger when HeldDuration reaches the threshold
	bool bIsFirstTrigger = !bTriggered;
	bTriggered = HeldDuration >= HoldTimeThreshold;
	if (bTriggered)
	{
		return (bIsFirstTrigger || !bIsOneShot) ? ETriggerState::Triggered : ETriggerState::None;
	}

	return State;
}