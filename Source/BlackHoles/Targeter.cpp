// Fill out your copyright notice in the Description page of Project Settings.


#include "Targeter.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "FirstPersonCharacter.h"

// Sets default values for this component's properties
UTargeter::UTargeter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTargeter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTargeter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

UPhysicsHandleComponent* UTargeter::GetPhysicsHandle()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Physics Handle - nullptr"));
	}
	return PhysicsHandle;
}

void UTargeter::Target()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult Target;
	bool HasTarget = GetTargetableInReach(Target);

	AFirstPersonCharacter* OwnerPlayerChar = Cast<AFirstPersonCharacter>(GetOwner());

	if (HasTarget)
	{
		TargetedActor = Target.GetActor();
		UPrimitiveComponent* TargetedComponent = Target.GetComponent();

		TArray<FName>& TargetedActorTags = TargetedActor->Tags;
		UE_LOG(LogTemp, Display, TEXT("Number of tags on grabbed actor: %d"), TargetedActorTags.Num());

		if (!TargetedActorTags.Contains("Targeted"))
		{
			if (OwnerPlayerChar)
				OwnerPlayerChar->SetImmobilized(true);

			TargetedComponent->WakeAllRigidBodies();
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				TargetedComponent,
				NAME_None,
				Target.ImpactPoint,
				GetComponentRotation()
			);

			// Add shake scene component to actor
			TargetedActor->AddComponentByClass(ShakeClass, false, FTransform::Identity, false);

			
			TargetedActorTags.Add("Targeted");
			UE_LOG(LogTemp, Display, TEXT("Number of tags POST TARGET: %d"), TargetedActorTags.Num());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s already targeted"), *TargetedActor->GetActorLabel());
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("NO HIT"));
	}
}

bool UTargeter::GetTargetableInReach(FHitResult& OutHit) const
{
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * MaxTargetDist;

	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Cyan);
	DrawDebugSphere(GetWorld(), LineEnd, 10, 20, FColor::Green, false, 5.0F);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(TargetRadius);

	return GetWorld()->SweepSingleByChannel(
		OutHit,
		LineStart,
		LineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere
	);
}


void UTargeter::Release(bool bBlackHoleIsTriggered)
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	UE_LOG(LogTemp, Display, TEXT("Inside Release Function"));

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		UE_LOG(LogTemp, Display, TEXT("Release Function if statement"));
		AFirstPersonCharacter* OwnerPlayerChar = Cast<AFirstPersonCharacter>(GetOwner());

		if (OwnerPlayerChar)
		{
			UE_LOG(LogTemp, Display, TEXT("Release Function owner player char check"));
			OwnerPlayerChar->SetImmobilized(false);
		}

		if (UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent())
		{
			if (bBlackHoleIsTriggered)
			{
				UE_LOG(LogTemp, Warning, TEXT("Spawning BH Sphere"));

				GetWorld()->SpawnActor<AActor>(
					BHOriginClass,
					GrabbedComponent->GetCenterOfMass(),
					GrabbedComponent->GetOwner()->GetActorRotation()
				);

			}
			

			GrabbedComponent->WakeAllRigidBodies();

			if (!GrabbedComponent->GetOwner()) return;
			GrabbedComponent->GetOwner()->Tags.Remove("Targeted");

			if (!ShakeClass) return;
			GrabbedComponent->GetOwner()->GetComponentByClass(ShakeClass)->DestroyComponent();

			PhysicsHandle->ReleaseComponent();
			TargetedActor = nullptr;
			UE_LOG(LogTemp, Display, TEXT("Released Component"));
		}

			

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Nothing Released"));
	}
}

