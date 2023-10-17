// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_UI/HTL_HudOverlay.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HTL_Characters/HTL_Player.h"

void UHTL_HudOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerRef = Cast<AHTL_Player>( UGameplayStatics::GetPlayerCharacter(this, 0));
}

void UHTL_HudOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D ViewportSize = FVector2D::ZeroVector;

	UCameraComponent* Camera = PlayerRef->GetCameraComponent();
	
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	float ViewPortAspectRation = ViewportSize.X / ViewportSize.Y;
	float DesiredAspectRatio = Camera->AspectRatio;

	SetRenderScale(FVector2D(DesiredAspectRatio / ViewPortAspectRation, DesiredAspectRatio / ViewPortAspectRation));
}
