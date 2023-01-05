// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerController.h"

#include "Blueprint/UserWidget.h"

void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDClass)
	{
		HUDWidget = CreateWidget(this, HUDClass);
		HUDWidget->AddToViewport();
	}
}