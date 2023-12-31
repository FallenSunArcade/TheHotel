﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "HTL/Public/HTL_Characters/HTL_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HTL_Controllers/HTL_PlayerController.h"


AHTL_Player::AHTL_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f); 
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AHTL_Player::LayPlayerDown()
{
	CameraTargetHeight = -60.f;
	
	FirstPersonCameraComponent->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	FirstPersonCameraComponent->PostProcessSettings.DepthOfFieldFocalDistance = CurrentDOFFD;
	
	FirstPersonCameraComponent->PostProcessSettings.bOverride_DepthOfFieldDepthBlurRadius = true;
	FirstPersonCameraComponent->PostProcessSettings.DepthOfFieldDepthBlurRadius  = CurrentDOFBR;
}

void AHTL_Player::StartPickUpTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHTL_Player::PickPlayerUp, GetupDelay, false);
}

void AHTL_Player::PickPlayerUp()
{
	TargetRoll = 0.f;
	CameraTargetHeight = 60.f;
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(WalkCameraShakeClass, 5);

	if (AHTL_PlayerController* PlayerController = Cast<AHTL_PlayerController>(Controller))
	{
		PlayerController->SetInputModeGameOnly();
	}
}

void AHTL_Player::PlayerDied(bool bHell)
{
	if (AHTL_PlayerController* PlayerController = Cast<AHTL_PlayerController>(Controller))
	{
		PlayerController->HandlePassingOut(bHell);
	}
}

void AHTL_Player::BeginPlay()
{
	Super::BeginPlay();

	TargetSpeed = WalkSpeed;

	AddControllerRollInput(CurrentRoll);
	
	PlayerControllerRef = Cast<AHTL_PlayerController>(Controller);
	
	if (PlayerControllerRef)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerRef->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AHTL_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		CurrentRoll = FMath::FInterpTo(CurrentRoll, TargetRoll, DeltaTime, 2.f);
		FRotator CurrentRotation = GetControlRotation();
		PlayerControllerRef->SetControlRotation({CurrentRotation.Pitch, CurrentRotation.Yaw, CurrentRoll});
	}

	
	CameraCurrentHeight = FMath::FInterpTo(CameraCurrentHeight, CameraTargetHeight, DeltaTime, 2.f);
	FirstPersonCameraComponent->SetRelativeLocation({0, 0, CameraCurrentHeight});

	FirstPersonCameraComponent->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	CurrentDOFFD = FMath::FInterpTo(CurrentDOFFD, TargetDOFFD, DeltaTime, 2.f);
	FirstPersonCameraComponent->PostProcessSettings.DepthOfFieldFocalDistance = CurrentDOFFD;

	FirstPersonCameraComponent->PostProcessSettings.bOverride_DepthOfFieldDepthBlurRadius = true;
	CurrentDOFBR = FMath::FInterpTo(CurrentDOFBR, TargetDOFBR, DeltaTime, 2.f);
	FirstPersonCameraComponent->PostProcessSettings.DepthOfFieldDepthBlurRadius  = CurrentDOFBR;
	
	// For Crouching
	if(bIsCrouching)
	{
		CurrentCapsuleHeight = FMath::FInterpTo(CurrentCapsuleHeight, CrouchCapsuleHeight, DeltaTime, CrouchingInterpSpeed);
	}
	else
	{
		CurrentCapsuleHeight = FMath::FInterpTo(CurrentCapsuleHeight, StandingCapsuleHeight, DeltaTime, CrouchingInterpSpeed);
	}

	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, SprintingInterpSpeed);

	const float Speed = GetVelocity().Length();
	EMovementState NewMovementState;
	
	if(Speed <= 0.f || GetCharacterMovement()->IsFalling())
	{
		NewMovementState = EMovementState::Idle;
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(IdleCameraShakeClass);
	}
	else if(Speed == SprintSpeed)
	{
		NewMovementState = EMovementState::Sprinting;
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(WalkCameraShakeClass, 1);
	}
	else
	{
		NewMovementState = EMovementState::Walking;
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(WalkCameraShakeClass, 2);
	}

	if(MovementState != NewMovementState)
	{
		UpdateMovement(NewMovementState);
		MovementState = NewMovementState;
	}
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(CurrentCapsuleHeight);
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}

void AHTL_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHTL_Player::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHTL_Player::Look);
		EnhancedInputComponent->BindAction(StartCrouchAction, ETriggerEvent::Triggered, this, &AHTL_Player::StartCrouch);
		EnhancedInputComponent->BindAction(EndCrouchAction, ETriggerEvent::Triggered, this, &AHTL_Player::EndCrouch);
		EnhancedInputComponent->BindAction(StartSprintAction, ETriggerEvent::Triggered, this, &AHTL_Player::StartSprint);
		EnhancedInputComponent->BindAction(EndSprintAction, ETriggerEvent::Triggered, this, &AHTL_Player::EndSprint);
		EnhancedInputComponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &AHTL_Player::ZoomIn);
		EnhancedInputComponent->BindAction(StopZoomInAction, ETriggerEvent::Triggered, this, &AHTL_Player::StopZoomIn);
		EnhancedInputComponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &AHTL_Player::ZoomOut);
		EnhancedInputComponent->BindAction(StopZoomOutAction, ETriggerEvent::Triggered, this, &AHTL_Player::StopZoomOut);
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Triggered, this, &AHTL_Player::PauseMenu);
	}
}

void AHTL_Player::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AHTL_Player::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHTL_Player::StartCrouch(const FInputActionValue& Value)
{
	if(!bIsSprinting)
	{
		bIsCrouching = true;
		TargetSpeed = CrouchSpeed;
		GetCharacterMovement()->MinAnalogWalkSpeed = 10.f;
	}
}

void AHTL_Player::EndCrouch(const FInputActionValue& Value)
{
	if(!bIsSprinting)
	{
		bIsCrouching = false;
		TargetSpeed = WalkSpeed;
		GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	}
}

void AHTL_Player::StartSprint(const FInputActionValue& Value)
{
	bIsSprinting = true;
	bIsCrouching = false;

	TargetSpeed = SprintSpeed;
}

void AHTL_Player::EndSprint(const FInputActionValue& Value)
{
	bIsSprinting = false;

	TargetSpeed = WalkSpeed;
}

void AHTL_Player::ZoomIn(const FInputActionValue& Value)
{
	CurrentFOV = FMath::FInterpTo(CurrentFOV, MaxZoom, GetWorld()->GetDeltaSeconds(), ZoomSpeed);
		
	FirstPersonCameraComponent->SetFieldOfView(CurrentFOV);

	if(CurrentFOV > (MaxZoom + 1))
	{
		ZoomingCamera(true);
	}
	else
	{
		ZoomingCamera(false);
	}
}

void AHTL_Player::StopZoomIn(const FInputActionValue& Value)
{
	ZoomingCamera(false);
}

void AHTL_Player::StopZoomOut(const FInputActionValue& Value)
{
	ZoomingCamera(false);
}

void AHTL_Player::PauseMenu(const FInputActionValue& Value)
{
	PlayerControllerRef->OpenPauseMenu();
}

void AHTL_Player::ZoomOut(const FInputActionValue& Value)
{
	constexpr float StartSpeed = 1.0f; 
	constexpr float MaxSpeed = 5.0f;
	
	const float DistanceToTarget = FMath::Abs(90.f - CurrentFOV);

	const float DynamicInterpSpeed = FMath::Lerp(MaxSpeed, StartSpeed, DistanceToTarget / 100.0f); 
	
	CurrentFOV = FMath::FInterpTo(CurrentFOV, 90, GetWorld()->GetDeltaSeconds(), DynamicInterpSpeed);
		
	FirstPersonCameraComponent->SetFieldOfView(CurrentFOV);

	if(CurrentFOV < 89)
	{
		ZoomingCamera(true);
	}
	else
	{
		ZoomingCamera(false);
	}
}

