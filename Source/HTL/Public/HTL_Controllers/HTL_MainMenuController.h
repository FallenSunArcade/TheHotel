﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HTL_MainMenuController.generated.h"

class UHTL_MainMenu;
class UMediaPlayer;
class UMediaSource;
class UMediaSoundComponent;

UCLASS()
class HTL_API AHTL_MainMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	AHTL_MainMenuController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void GameStarted();

	UFUNCTION()
	void OnMediaFinished();

	UFUNCTION()
	void DelayedStart();

	UFUNCTION()
	void DelayedStart2();
	
private:
	UPROPERTY(EditAnywhere, Category = "Intro Video")
	UMediaPlayer* IntroMediaPlayer;
    
	UPROPERTY(EditAnywhere, Category = "Intro Video")
	UMediaSource* IntroMediaSource;

	UPROPERTY(EditAnywhere, Category = "Intro Video")
	UMediaSoundComponent* MediaSound;
	
	UPROPERTY(EditAnywhere, Category = "Menu")
	TSubclassOf<UHTL_MainMenu> MenuWidgetClass;

	UPROPERTY()
	UHTL_MainMenu* MainMenuRef = nullptr;

	FTimerHandle IntroPlayDelayHandle;
};
