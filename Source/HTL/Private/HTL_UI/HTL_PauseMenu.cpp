// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_UI/HTL_PauseMenu.h"
#include "Components/Button.h"

void UHTL_PauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UHTL_PauseMenu::StartButtonClicked);
	}
}

void UHTL_PauseMenu::StartButtonClicked()
{
	ContinueDelegate.Broadcast();
}
