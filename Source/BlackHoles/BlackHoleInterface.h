// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UBlackHoleInterface : public UInterface
{
	GENERATED_BODY()
};


class IBlackHoleInterface
{
	GENERATED_BODY()
	

protected:

	virtual void DestroySelf();

protected:

	UPROPERTY(EditAnywhere, Category = "FX")
	class USoundBase* PersistentSound;

	UPROPERTY(EditAnywhere)
	float SelfDestroyTimer = 5.f;

};
