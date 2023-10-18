// Fill out your copyright notice in the Description page of Project Settings.

#include "HTL/Public/HTL_Characters/HTL_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"


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

void AHTL_Player::BeginPlay()
{
	Super::BeginPlay();

	TargetSpeed = WalkSpeed;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AHTL_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
	
	if(Speed <= 0.f)
	{
		NewMovementState = EMovementState::Idle;
	}
	else if(Speed == SprintSpeed)
	{
		NewMovementState = EMovementState::Sprinting;
	}
	else
	{
		NewMovementState = EMovementState::Walking;
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
		EnhancedInputComponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &AHTL_Player::ZoomOut);
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
	FVector2D LookAxisVector = Value.Get<FVector2D>();

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
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("CurrentFOV: %f"), CurrentFOV));
	}
}

void AHTL_Player::ZoomOut(const FInputActionValue& Value)
{
	CurrentFOV = FMath::FInterpTo(CurrentFOV, 90, GetWorld()->GetDeltaSeconds(), ZoomSpeed);
		
	FirstPersonCameraComponent->SetFieldOfView(CurrentFOV);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("CurrentFOV: %f"), CurrentFOV));
	}
}

