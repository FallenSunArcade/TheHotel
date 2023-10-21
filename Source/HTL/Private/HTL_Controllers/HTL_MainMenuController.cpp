// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_MainMenuController.h"
#include "MediaPlayer.h"
#include "HTL_Actors/HTL_CameraActor.h"
#include "HTL_UI/HTL_MainMenu.h"
#include "Kismet/GameplayStatics.h"

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
			MainMenuRef->StartDelegate.AddDynamic(this, &AHTL_MainMenuController::GameStarted);
			SetShowMouseCursor(true);
		}
	}
}

void AHTL_MainMenuController::GameStarted()
{
	AHTL_CameraActor* CameraActor = Cast<AHTL_CameraActor>(GetViewTarget());
	CameraActor->StartPressed();

	if (IntroMediaPlayer && IntroMediaSource)
	{
		IntroMediaPlayer->OnEndReached.AddDynamic(this, &AHTL_MainMenuController::OnMediaFinished);
		IntroMediaPlayer->OpenSource(IntroMediaSource);
		IntroMediaPlayer->Play();
		IntroMediaPlayer->SetLooping(false);
	}
}

void AHTL_MainMenuController::OnMediaFinished()
{
	UGameplayStatics::OpenLevel(this, TEXT("Level1"));
}
