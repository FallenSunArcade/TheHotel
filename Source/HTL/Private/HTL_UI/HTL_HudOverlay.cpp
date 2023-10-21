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
		StartTransition(WhiteTransition, IsFadeOut, Delay);
	}
	else
	{
		StartTransition(BlackTransition, IsFadeOut, Delay);
	}
}

void UHTL_HudOverlay::FadingOut()
{
	Opacity -= .05f;
	if(Opacity > 0.f)
	{
		CurrentTransition->SetOpacity(Opacity);
	}
	else
	{
		CurrentTransition->SetOpacity(0.f);
		GetWorld()->GetTimerManager().ClearTimer(GameTransitionHandle);
		TransitionEndedDelegate.Broadcast();
		UE_LOG(LogTemp, Display, TEXT("Transition done (%s)"), *GetName());
	}
}

void UHTL_HudOverlay::StartTransition(UImage* Transition, bool IsFadeOut, float Delay)
{
	if(Transition)
	{
		if(IsFadeOut)
		{
			CurrentTransition = Transition;
			Opacity = 1.f;
			Transition->SetOpacity(1.f);
			GetWorld()->GetTimerManager().SetTimer(GameTransitionHandle, this, &UHTL_HudOverlay::FadingOut, .1f, true, Delay);
		}
		else
		{
			
		}
	}
}

