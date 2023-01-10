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

	AFirstPersonCharacter();

private:

	// DEFAULT COMPONENTS

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


	// INPUTS

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* SummonBlackHoleAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* CompressTargetAction;

	int32 InputMappingPriority = 0;


	// MOVEMENT

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardBackSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SideSpeed = 200.f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsImmobilized = false;


	// FX

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* BHGenesisParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ABlackHoleProjectile> BlackHoleProjectileClass;

	
protected:

	virtual void BeginPlay() override;

	void SetInputMappings();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetImmobilized(bool);

private:

	// -- INPUT CALLBACKS -- //

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	// Abilities

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

	


};
