// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HTL_Controllers/HTL_OutroController.h"
#include "Components/SkeletalMeshComponent.h"

AHTL_CameraActor::AHTL_CameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneComponent);

	TV = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TV"));
	TV->SetupAttachment(RootComponent);

	VCR = CreateDefaultSubobject<USkeletalMeshComponent>("VCR");
	VCR->SetupAttachment(RootComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AHTL_CameraActor::StartVideo()
{
	if(IntroMaterial)
	{
		TV->SetMaterial(1, IntroMaterial);
	}
}

void AHTL_CameraActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this);

	if(bIsOutro)
	{
		if(AHTL_OutroController* OutroController = Cast<AHTL_OutroController>(PlayerController))
		{
			OutroController->StartOutroVideo(this);
		}
	}
}

void AHTL_CameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bStartPressed && ActorToLerpTo)
	{
		FVector CurrentLocation = GetActorLocation();
		FRotator CurrentRotation = GetActorRotation();

		if(CurrentLocation != ActorToLerpTo->GetActorLocation() && CurrentRotation != ActorToLerpTo->GetActorRotation())
		{
			FVector NewLocation = FMath::VInterpTo(CurrentLocation, ActorToLerpTo->GetActorLocation(), DeltaTime, MovementInterpolationSpeed);
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, ActorToLerpTo->GetActorRotation(), DeltaTime, MovementInterpolationSpeed);
		
			SetActorLocation(NewLocation);
			SetActorRotation(NewRotation);
		}
		else
		{
			TV->SetMaterial(0, Transparent);
			TV->SetMaterial(2, Transparent);
		}

	}
}

void AHTL_CameraActor::SetOutroMaterial(UMaterialInterface* OutroMaterial)
{
	if(OutroMaterial)
	{
		TV->SetMaterial(0, OutroMaterial);
	}
}

void AHTL_CameraActor::InsertTape()
{
	VCR->GetAnimInstance()->Montage_Play(InsertTapeMontage);
}

void AHTL_CameraActor::PanIn()
{
	TV->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	VCR->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	
	bStartPressed = true;
}


