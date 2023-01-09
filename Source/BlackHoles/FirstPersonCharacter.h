// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"


class UInputAction;
class ABlackHoleProjectile;
class UParticleSystem;
class UParticleSystemComponent;

UCLASS()
class BLACKHOLES_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* FormationParticles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UTargeter* Targeter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetInputMappings();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetImmobilized(bool);

private:

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void StartSummonBlackHole(const FInputActionValue& Value);

	UFUNCTION()
	void LaunchBlackHole(const FInputActionValue& Value);

	UFUNCTION()
	void CancelBlackHole(const FInputActionValue& Value);

	UFUNCTION()
	void StartCompressTarget(const FInputActionValue& Value);

	UFUNCTION()
	void CompressTarget(const FInputActionValue& Value);

	UFUNCTION()
	void CancelCompressTarget(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	int32 InputMappingPriority = 0;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* SummonBlackHoleAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* CompressTargetAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardBackSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SideSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ABlackHoleProjectile> BlackHoleProjectileClass;	

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* BHGenesisParticles;

	

	UPROPERTY(VisibleAnywhere)
	bool bIsImmobilized = false;


};
