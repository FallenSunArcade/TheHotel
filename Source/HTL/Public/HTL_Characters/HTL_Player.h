﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "HTL_Player.generated.h"

class AHTL_PlayerController;

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
class UCameraShakeBase;

UCLASS()
class HTL_API AHTL_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AHTL_Player();

	UCameraComponent* GetCameraComponent() const {return FirstPersonCameraComponent;}

	void LayPlayerDown();

	void StartPickUpTimer();
	
	UFUNCTION()
	void PickPlayerUp();

	void PlayerDied(bool bHell);
	
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

	void ZoomIn(const FInputActionValue& Value);
	
	void StopZoomIn(const FInputActionValue& Value);

	void ZoomOut(const FInputActionValue& Value);
	
	void StopZoomOut(const FInputActionValue& Value);

	void PauseMenu(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMovement(const EMovementState& State);

	UFUNCTION(BlueprintImplementableEvent)
	void ZoomingCamera(bool IsZooming);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MaxZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> IdleCameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> WalkCameraShakeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StartCrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EndCrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StartSprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EndSprintAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomInAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StopZoomInAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomOutAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StopZoomOutAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Get up", meta = (AllowPrivateAccess = "true"))
	float GetupDelay = 5.f;

	UPROPERTY()
	AHTL_PlayerController* PlayerControllerRef = nullptr;

	float CurrentSpeed = 0.f;

	float TargetSpeed = 0.f;

	bool bIsSprinting = false;

	bool bIsCrouching = false;

	// For Camera Interpolation
	float TargetFOV = 0.f;

	float CurrentFOV = 90.f;

	float CameraTargetHeight = 0.f;

	float CameraCurrentHeight = 0.f;

	float TargetDOFFD = 0.f;

	float TargetDOFBR = 0.f;

	float CurrentDOFFD = 1.f;

	float CurrentDOFBR = 1.f;

	float CurrentRoll = 30.f;

	float TargetRoll = 30.f;

	FTimerHandle TimerHandle;
};
