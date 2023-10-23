// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HTL_HudOverlay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTransitionEndedDelegate, bool, IsFadeOut);

class UImage;

UCLASS()
class HTL_API UHTL_HudOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void StartGameTransition(bool IsFadeOut, float Delay, bool IsWhite);

	void SetBadEndingOpacity(float NewOpacity);

	UFUNCTION()
	void FadingOut();

	UFUNCTION()
	void FadingIn();
	
	UPROPERTY(BlueprintAssignable)
	FTransitionEndedDelegate TransitionEndedDelegate;
	
protected:
	void StartTransition(bool IsFadeOut, float Delay);
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Overlay = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* BadEnding = nullptr;
	
	FTimerHandle GameTransitionHandle;

	float Opacity = 0.f;
};
