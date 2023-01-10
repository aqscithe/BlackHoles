// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleStatic.h"

// Sets default values
ABlackHoleStatic::ABlackHoleStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

}

// Called when the game starts or when spawned
void ABlackHoleStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHoleStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

