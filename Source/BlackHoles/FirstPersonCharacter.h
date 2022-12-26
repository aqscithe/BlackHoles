// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"


class UInputAction;

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
	USceneComponent* ProjectileSpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	int32 InputMappingPriority = 0;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	const UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardBackSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SideSpeed = 200.f;
	

	//void MoveRight(float AxisValue);
	//void LookRight(float AxisValue);
	//void LookUp(float AxisValue);
	//
	//void LookRightRate(float AxisValue);
	//void LookUpRate(float AxisValue);

};
