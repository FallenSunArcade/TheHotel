// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_MainMenuController.h"
#include "HTL_UI/HTL_MainMenu.h"

AHTL_MainMenuController::AHTL_MainMenuController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHTL_MainMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);
	FlushPressedKeys();
	
	if(*MenuWidgetClass)
	{
		MainMenuRef = CreateWidget<UHTL_MainMenu>(this, MenuWidgetClass);

		if(MainMenuRef)
		{
			MainMenuRef->AddToViewport();
			MainMenuRef->SetVisibility(ESlateVisibility::Visible);
			SetShowMouseCursor(true);
		}
	}
}
