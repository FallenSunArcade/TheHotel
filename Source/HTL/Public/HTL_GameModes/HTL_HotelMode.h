// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HTL_HotelMode.generated.h"

class AHTL_MainMenuController;
class AHTL_PlayerController;

UENUM()
enum class EHotelStates : uint8
{
	Menu,
	Hotel
};

UCLASS()
class HTL_API AHTL_HotelMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Game State")
	EHotelStates HotelState = EHotelStates::Menu;

	UPROPERTY()
	AHTL_MainMenuController* MainMenuController = nullptr;
};
