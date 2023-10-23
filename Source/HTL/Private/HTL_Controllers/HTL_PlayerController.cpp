// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_PlayerController.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "HTL_Characters/HTL_Player.h"
#include "Kismet/GameplayStatics.h"
#include "HTL_UI/HTL_HudOverlay.h"
#include "HTL_UI/HTL_PauseMenu.h"

AHTL_PlayerController::AHTL_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHTL_PlayerController::MakeTransition(bool IsFadeOut, float Delay, bool IsWhite)
{
	if(IsFadeOut)
	{
		if(AHTL_Player* PlayerCharacter = Cast<AHTL_Player>(UGameplayStatics::GetPlayerCharacter(this, 0)))
		{
			PlayerCharacter->LayPlayerDown();
		}
	}
	
	const FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(false);
	FlushPressedKeys();
	HudOverlayRef->StartGameTransition(IsFadeOut, Delay, IsWhite);
}

void AHTL_PlayerController::TransitionEnded(bool IsFadeOut)
{
	if (IsFadeOut)
	{
		if (AHTL_Player* PlayerCharacter = Cast<AHTL_Player>(UGameplayStatics::GetPlayerCharacter(this, 0)))
		{
			PlayerCharacter->StartPickUpTimer();
		}
	}
	else
	{
		UGameplayStatics::OpenLevel(this, TEXT("OutroLevel"));
	}
}

void AHTL_PlayerController::ContinuePressed()
{
	SetPause(false);
	SetInputModeGameOnly();
}

void AHTL_PlayerController::SetInputModeGameOnly()
{
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
	FlushPressedKeys();
}

void AHTL_PlayerController::HandlePassingOut(bool Hell)
{
	if(Hell)
	{
		MakeTransition(false, .5f, false);
	}
	else
	{
		MakeTransition(false, .5f, true);
	}
}

void AHTL_PlayerController::OpenPauseMenu()
{
	const FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
	FlushPressedKeys();
	
	PauseRef->AddToViewport();
	Pause();
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
			HudOverlayRef->TransitionEndedDelegate.AddDynamic(this, &AHTL_PlayerController::AHTL_PlayerController::TransitionEnded);
		}
	}

	if(*PauseWidgetClass)
	{
		PauseRef = CreateWidget<UHTL_PauseMenu>(this, PauseWidgetClass);
		PauseRef->ContinueDelegate.AddDynamic(this, &AHTL_PlayerController::AHTL_PlayerController::ContinuePressed);
	}

	MakeTransition(true, 1.f, false);
}
