// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HTL_PlayerController.generated.h"

class UHTL_PauseMenu;
class UHTL_HudOverlay;
class AHTL_HotelMode;

UCLASS()
class HTL_API AHTL_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHTL_PlayerController();

	void MakeTransition(bool IsFadeOut, float Delay, bool IsWhite);

	UFUNCTION()
	void TransitionEnded(bool IsFadeOut);

	UFUNCTION()
	void ContinuePressed();

	void SetInputModeGameOnly();

	void HandlePassingOut(bool Hell);

	void OpenPauseMenu();
	
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "User Interface")
	TSubclassOf<UHTL_HudOverlay> HudOverlayWidgetClass;

	UPROPERTY(EditAnywhere, Category = "User Interface")
	TSubclassOf<UHTL_PauseMenu> PauseWidgetClass;
	
	UPROPERTY()
	UHTL_HudOverlay* HudOverlayRef = nullptr;

	UPROPERTY()
	UHTL_PauseMenu* PauseRef = nullptr;

	UPROPERTY()
	AHTL_HotelMode* HotelGameMode = nullptr;
};
