// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UProjectileMovementComponent;
class USoundBase;

UCLASS()
class BLACKHOLES_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();


protected:

	// COMPONENTS

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComp;

	// MODIFIABLE MEMBERS

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 0.f;


protected:

	virtual void BeginPlay() override;

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);
	

public:	
	virtual void Tick(float DeltaTime) override;

};

