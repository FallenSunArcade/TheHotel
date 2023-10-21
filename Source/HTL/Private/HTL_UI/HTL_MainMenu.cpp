// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_UI/HTL_MainMenu.h"
#include "Components/Button.h"

void UHTL_MainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UHTL_MainMenu::StartButtonClicked);
	}
}

void UHTL_MainMenu::StartButtonClicked()
{
	StartDelegate.Broadcast();
}
