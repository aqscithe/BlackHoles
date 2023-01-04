// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "BlackHoleProjectile.generated.h"

class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class BLACKHOLES_API ABlackHoleProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	ABlackHoleProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrailParticles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* RingParticles;

	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* TractionFX;

	UPROPERTY(EditAnywhere, Category = "FX")
	class USoundBase* PersistentSound;


protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult) override;
	
private:	

	void DestroyBH();

	UPROPERTY(EditAnywhere)
	float BlackHoleDestructionTimer = 5.f;

	FTimerHandle BlackHoleDestructionTimerHandle;
};
