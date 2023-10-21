// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HTL_HudOverlay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTransitionEndedDelegate);

class UImage;

UCLASS()
class HTL_API UHTL_HudOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void StartGameTransition(bool IsFadeOut, float Delay, bool IsWhite);

	UFUNCTION()
	void FadingOut();
	
	UPROPERTY(BlueprintAssignable)
	FTransitionEndedDelegate TransitionEndedDelegate;
	
protected:
	void StartTransition(UImage* Transition, bool IsFadeOut, float Delay);
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* WhiteTransition = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* BlackTransition = nullptr;

	UPROPERTY()
	UImage* CurrentTransition = nullptr;
	
	FTimerHandle GameTransitionHandle;

	float Opacity = 0.f;
};
