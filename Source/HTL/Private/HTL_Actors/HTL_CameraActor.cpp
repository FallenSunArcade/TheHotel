// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AHTL_CameraActor::AHTL_CameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneComponent);

	TV = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TV"));
	TV->SetupAttachment(RootComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AHTL_CameraActor::StartPressed()
{
	TV->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	if(IntroMaterial)
	{
		TV->SetMaterial(4, IntroMaterial);
	}
	bStartPressed = true;
}

void AHTL_CameraActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this);
}

void AHTL_CameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bStartPressed)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, ActorToLerpTo->GetActorLocation(), DeltaTime, MovementInterpolationSpeed);
		SetActorLocation(NewLocation);
	}
}

