// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_MainMenuController.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "HTL_Actors/HTL_CameraActor.h"
#include "HTL_UI/HTL_MainMenu.h"
#include "Kismet/GameplayStatics.h"

AHTL_MainMenuController::AHTL_MainMenuController()
{
	PrimaryActorTick.bCanEverTick = true;

	MediaSound = CreateDefaultSubobject<UMediaSoundComponent>("Media Sound");
	RootComponent = MediaSound;
}

void AHTL_MainMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (IntroMediaPlayer)
	{
		MediaSound->SetMediaPlayer(IntroMediaPlayer);
	}
	
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
	CameraActor->InsertTape();
	GetWorld()->GetTimerManager().SetTimer(IntroPlayDelayHandle, this, &AHTL_MainMenuController::DelayedStart, 2.f, false);
}

void AHTL_MainMenuController::OnMediaFinished()
{
	UGameplayStatics::OpenLevel(this, TEXT("Level1"));
}

void AHTL_MainMenuController::DelayedStart()
{
	AHTL_CameraActor* CameraActor = Cast<AHTL_CameraActor>(GetViewTarget());
	CameraActor->PanIn();

	GetWorld()->GetTimerManager().SetTimer(IntroPlayDelayHandle, this, &AHTL_MainMenuController::DelayedStart2, 4.5f, false);
}

void AHTL_MainMenuController::DelayedStart2()
{
	AHTL_CameraActor* CameraActor = Cast<AHTL_CameraActor>(GetViewTarget());
	CameraActor->StartVideo();
	if (IntroMediaPlayer && IntroMediaSource)
	{
		IntroMediaPlayer->OnEndReached.AddDynamic(this, &AHTL_MainMenuController::OnMediaFinished);
		IntroMediaPlayer->OpenSource(IntroMediaSource);
		IntroMediaPlayer->Play();
		IntroMediaPlayer->SetLooping(false);
	}
}
