// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class BLACKHOLES_API AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUDWidget;
	
};
