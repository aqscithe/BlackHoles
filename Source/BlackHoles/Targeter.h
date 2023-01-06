// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Targeter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKHOLES_API UTargeter : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargeter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Target();

	void Release();

private:

	class UPhysicsHandleComponent* GetPhysicsHandle();

	bool GetTargetableInReach(FHitResult& OutHit) const;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UActorComponent> ShakeClass;


	UPROPERTY(EditAnywhere)
	float MaxTargetDist = 400.f;

	UPROPERTY(EditAnywhere)
	float TargetRadius = 100.f;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200.f;
};
