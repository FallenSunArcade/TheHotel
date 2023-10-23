// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_OutroController.h"
#include "HTL_GameInstances/HTL_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MediaPlayer.h"
#include "HTL_Actors/HTL_CameraActor.h"
#include "MediaSoundComponent.h"


AHTL_OutroController::AHTL_OutroController()
{
	MediaSound = CreateDefaultSubobject<UMediaSoundComponent>("Media Sound");
	RootComponent = MediaSound;
}

void AHTL_OutroController::StartOutroVideo(AHTL_CameraActor* Camera)
{
	if(const UHTL_GameInstance* GameInstance = Cast<UHTL_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		if(OutroMaterial && OutroMediaPlayer)
		{
			Camera->SetOutroMaterial(OutroMaterial);
			OutroMediaPlayer->OnEndReached.AddDynamic(this, &AHTL_OutroController::OnMediaFinished);
			
					
			if(GameInstance->GetWasEndingBad())
			{
				if (BadOutroMediaSource)
				{
					OutroMediaPlayer->OpenSource(BadOutroMediaSource);
				}
			}
			else
			{
				if (GoodOutroMediaSource)
				{
					OutroMediaPlayer->OpenSource(GoodOutroMediaSource);
				}
			}
		}
	}
}

void AHTL_OutroController::OnMediaFinished()
{
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
}

void AHTL_OutroController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);
	FlushPressedKeys();

	if (OutroMediaPlayer)
	{
		MediaSound->SetMediaPlayer(OutroMediaPlayer);
	}
}
