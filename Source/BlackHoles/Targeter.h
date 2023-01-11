// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Targeter.generated.h"

class UPhysicsHandleComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKHOLES_API UTargeter : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargeter();

private:

	AActor* TargetedActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UActorComponent> ShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> BHOriginClass;


	UPROPERTY(EditAnywhere)
	float MaxTargetDist = 400.f;

	UPROPERTY(EditAnywhere)
	float TargetRadius = 100.f;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200.f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Target();

	bool ShakeTarget(UPrimitiveComponent* TargetedComponent, UPhysicsHandleComponent* PhysicsHandle, FHitResult& Target);

	void Release(bool bBlackHoleIsTriggered = false);

private:

	UPhysicsHandleComponent* GetPhysicsHandle();

	bool GetTargetableInReach(FHitResult& OutHit) const;

	
};
