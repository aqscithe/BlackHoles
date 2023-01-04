// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "BlackHoleProjectile.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FP Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(Camera);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(SpringArm);

	FormationParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Formation Particles"));
	FormationParticles->SetupAttachment(ProjectileSpawnPoint);


}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Only doing this b/c I can't see the particles details in unreal editor
	if (FormationParticles && BHGenesisParticles)
	{
		FormationParticles->SetTemplate(BHGenesisParticles);
		FormationParticles->Deactivate();
	}
		

	SetInputMappings();

}

void AFirstPersonCharacter::SetInputMappings()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), InputMappingPriority);
			}
		}
	}
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Look);
		Input->BindAction(SummonBlackHoleAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::StartSummonBlackHole);
		Input->BindAction(SummonBlackHoleAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::LaunchBlackHole);
		Input->BindAction(SummonBlackHoleAction, ETriggerEvent::Canceled, this, &AFirstPersonCharacter::CancelBlackHole);
		Input->BindAction(CompressTargetAction, ETriggerEvent::Trigg, this, &AFirstPersonCharacter::CancelBlackHole);
	}
}

// Remember FInputActionInstance has access to more data
// Use FInputActionValue if that is all you need
void AFirstPersonCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);


	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y );

	const FVector SideDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(SideDirection, MovementVector.X);
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AFirstPersonCharacter::StartSummonBlackHole(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Summon Black Hole Particles"));
	UE_LOG(LogTemp, Warning, TEXT("Swirling black spheres particle effect."));

	if (FormationParticles)
		FormationParticles->Activate();
}

void AFirstPersonCharacter::LaunchBlackHole(const FInputActionValue& Value)
{
	if (FormationParticles)
		FormationParticles->Deactivate();

	if (BlackHoleProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawing and launching invisible Blackhole Mesh"));

		ABlackHoleProjectile* BHProjectile = GetWorld()->SpawnActor<ABlackHoleProjectile>(
			BlackHoleProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation()
		);

		if (BHProjectile)
			BHProjectile->SetOwner(this);
	}
	
}

void AFirstPersonCharacter::CancelBlackHole(const FInputActionValue& Value)
{
	if (FormationParticles)
		FormationParticles->Deactivate();

	// play cancel black hole particle

	// play cancel ability sound
}

void AFirstPersonCharacter::CompressTarget(const FInputActionValue& Value)
{
	// perhaps need to right click and hold ability button
	// Mouse over compressable object/enemy in environment
		// need crosshair
		// need line trace
		// outline(or some other identifying effect) for targeted object
	// Must hold for a couple seconds
	// object/enemy collapses in on it self and is completely destroyed
	// a black hole is left in its wake
	// black hole disappears after a few seconds
}



