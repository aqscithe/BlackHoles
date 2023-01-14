// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 15, FColor::Green, false, 15.f);
	
}

