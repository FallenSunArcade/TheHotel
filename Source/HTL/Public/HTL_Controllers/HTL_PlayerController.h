// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HTL_PlayerController.generated.h"

class UHTL_PauseMenu;
class UHTL_HudOverlay;
class AHTL_HotelMode;
class UMediaPlayer;
class UMediaSource;
class UMediaSoundComponent;


UCLASS()
class HTL_API AHTL_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHTL_PlayerController();

	void MakeTransition(bool IsFadeOut, float Delay, bool IsWhite);

	UFUNCTION()
	void TransitionEnded(bool IsFadeOut);

	void SetInputModeGameOnly();

	void HandlePassingOut();

	UFUNCTION()
	void OnMediaFinished();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Outro Video")
	UMediaPlayer* BadEndingMediaPlayer;
    
	UPROPERTY(EditAnywhere, Category = "Outro Video")
	UMediaSource* BadEndingMediaSource;

	UPROPERTY(EditAnywhere, Category = "Outro Video")
	UMediaSoundComponent* BadEndingMediaSound;
	
	UPROPERTY(EditAnywhere, Category = "User Interface")
	TSubclassOf<UHTL_HudOverlay> HudOverlayWidgetClass;

	UPROPERTY(EditAnywhere, Category = TV)
	UMaterialInterface* BadEndingMaterial = nullptr;
	
	UPROPERTY()
	UHTL_HudOverlay* HudOverlayRef = nullptr;

	UPROPERTY()
	AHTL_HotelMode* HotelGameMode = nullptr;
};
