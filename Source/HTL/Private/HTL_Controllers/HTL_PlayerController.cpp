// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "HTL_UI/HTL_HudOverlay.h"

AHTL_PlayerController::AHTL_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHTL_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
	FlushPressedKeys();
	
	if(*HudOverlayWidgetClass)
	{
		HudOverlayRef = CreateWidget<UHTL_HudOverlay>(this, HudOverlayWidgetClass);

		if(HudOverlayRef)
		{
			HudOverlayRef->AddToViewport();
			HudOverlayRef->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
