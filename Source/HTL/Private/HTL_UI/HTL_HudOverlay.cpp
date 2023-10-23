// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_UI/HTL_HudOverlay.h"
#include "Components/Image.h"

void UHTL_HudOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHTL_HudOverlay::StartGameTransition(bool IsFadeOut, float Delay, bool IsWhite)
{
	if(IsWhite)
	{
		StartTransition(IsFadeOut, Delay);
	}
	else
	{
		StartTransition(IsFadeOut, Delay);
	}
}

void UHTL_HudOverlay::FadingOut()
{
	Opacity -= .05f;

	Opacity = FMath::Clamp(Opacity, 0.f, 1.f);
	
	if(Opacity > 0.f)
	{
		Overlay->SetOpacity(Opacity);
	}
	else
	{
		Overlay->SetOpacity(0.f);
		GetWorld()->GetTimerManager().ClearTimer(GameTransitionHandle);
		TransitionEndedDelegate.Broadcast(true);
		UE_LOG(LogTemp, Display, TEXT("Transition done (%s)"), *GetName());
	}
}

void UHTL_HudOverlay::FadingIn()
{
	Opacity += .05f;
	
	Opacity = FMath::Clamp(Opacity, 0.f, 1.f);
	
	if(Opacity < 1.f)
	{
		Overlay->SetOpacity(Opacity);
	}
	else
	{
		Overlay->SetOpacity(1.f);
		GetWorld()->GetTimerManager().ClearTimer(GameTransitionHandle);
		TransitionEndedDelegate.Broadcast(false);
		UE_LOG(LogTemp, Display, TEXT("Transition done (%s)"), *GetName());
	}
}

void UHTL_HudOverlay::StartTransition(bool IsFadeOut, float Delay)
{
	if(Overlay)
	{
		if(IsFadeOut)
		{
			Opacity = 1.f;
			Overlay->SetOpacity(1.f);
			GetWorld()->GetTimerManager().SetTimer(GameTransitionHandle, this, &UHTL_HudOverlay::FadingOut, .1f, true, Delay);
		}
		else
		{
			Opacity = 0.f;
			Overlay->SetOpacity(0.f);
			GetWorld()->GetTimerManager().SetTimer(GameTransitionHandle, this, &UHTL_HudOverlay::FadingIn, .1f, true, Delay);
		}
	}
}

