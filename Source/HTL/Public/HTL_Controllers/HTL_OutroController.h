// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HTL_OutroController.generated.h"

class AHTL_CameraActor;
class UMediaPlayer;
class UMediaSource;
class UMediaSoundComponent;

UCLASS()
class HTL_API AHTL_OutroController : public APlayerController
{
	GENERATED_BODY()

public:
	AHTL_OutroController();

	void StartOutroVideo(AHTL_CameraActor* Camera);

	UFUNCTION()
	void OnMediaFinished();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Bad Outro Video")
	UMediaPlayer* OutroMediaPlayer;
	
	UPROPERTY(EditAnywhere, Category = "Bad Outro Video")
	UMaterialInterface* OutroMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = "Bad Outro Video")
	UMediaSource* BadOutroMediaSource;
	
	UPROPERTY(EditAnywhere, Category = "Good Outro Video")
	UMediaSource* GoodOutroMediaSource;

	UPROPERTY(EditAnywhere, Category = "Intro Video")
	UMediaSoundComponent* MediaSound;
};
