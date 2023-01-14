// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleProjectile.h"

#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"



ABlackHoleProjectile::ABlackHoleProjectile()
{
	ProjectileMovementComp->InitialSpeed = 0.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(RootComponent);

	RingParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ring Particles"));
	RingParticles->SetupAttachment(RootComponent);
}

void ABlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileMesh)
		ProjectileMesh->OnComponentHit.AddDynamic(this, &ABlackHoleProjectile::OnHit);
}

void ABlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABlackHoleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, HitResult);

	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Black Hole Hit %s"), *OtherActor->GetName());

		// change black hole ring particle effect to light being pulled in
		RingParticles->SetTemplate(TractionFX);
		// add timer to destroy BH
		GetWorldTimerManager().SetTimer(BlackHoleDestructionTimerHandle, this, &ABlackHoleProjectile::DestroyBH, BlackHoleDestructionTimer, false);
	}
}

void ABlackHoleProjectile::DestroyBH()
{
	Destroy();
}

void ABlackHoleProjectile::DestroySelf()
{
	Destroy();
}