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

	//UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	//
	//if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	//{
	//	if (AActor* TargetedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner())
	//	{
	//		// shake object
	//	}
	//}
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
		AActor* Actor = Target.GetActor();
		UPrimitiveComponent* TargetedComponent = Target.GetComponent();

		TArray<FName>& TargetedActorTags = Actor->Tags;
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
			Actor->AddComponentByClass(ShakeClass, false, FTransform::Identity, false);

			// need to still remove the component in the release function
			
			TargetedActorTags.Add("Targeted");
			UE_LOG(LogTemp, Display, TEXT("Number of tags POST TARGET: %d"), TargetedActorTags.Num());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s already targeted"), *Actor->GetActorLabel());
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


void UTargeter::Release()
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
			
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Targeted");
		PhysicsHandle->ReleaseComponent();

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Nothing Released"));
	}
}

