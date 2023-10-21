// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_GameModes/HTL_HotelMode.h"
#include "HTL_Controllers/HTL_MainMenuController.h"
#include "Kismet/GameplayStatics.h"

void AHTL_HotelMode::BeginPlay()
{
	Super::BeginPlay();

	switch (HotelState)
	{
	case EHotelStates::Menu:
		{
			MainMenuController = Cast<AHTL_MainMenuController>(UGameplayStatics::GetPlayerController(this, 0));
			break;
		}
	case EHotelStates::Hotel:
		break;
	default: ;
	}
}
