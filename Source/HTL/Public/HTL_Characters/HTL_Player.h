﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "HTL_Player.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle,
	Walking,
	Sprinting   
};

class UInputComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class HTL_API AHTL_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AHTL_Player();

	UCameraComponent* GetCameraComponent() const {return FirstPersonCameraComponent;}
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void StartCrouch(const FInputActionValue& Value);

	void EndCrouch(const FInputActionValue& Value);

	void StartSprint(const FInputActionValue& Value);

	void EndSprint(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMovement(const EMovementState& State);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* StartCrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EndCrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* StartSprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EndSprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchCapsuleHeight = 32.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float StandingCapsuleHeight = 88.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchingInterpSpeed = 10.f;

	float CurrentCapsuleHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float SprintingInterpSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	EMovementState MovementState = EMovementState::Idle;

	float CurrentSpeed = 0.f;

	float TargetSpeed = 0.f;

	bool bIsSprinting = false;

	bool bIsCrouching = false;
};
