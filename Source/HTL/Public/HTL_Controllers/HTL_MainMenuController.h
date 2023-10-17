// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HTL_MainMenuController.generated.h"

class UHTL_MainMenu;

UCLASS()
class HTL_API AHTL_MainMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	AHTL_MainMenuController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Menu")
	TSubclassOf<UHTL_MainMenu> MenuWidgetClass;

	UPROPERTY()
	UHTL_MainMenu* MainMenuRef = nullptr;
};
