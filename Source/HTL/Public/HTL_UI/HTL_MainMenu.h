// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HTL_MainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartDelegate);

class UButton;

UCLASS()
class HTL_API UHTL_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	FStartDelegate StartDelegate;
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void StartButtonClicked();
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton = nullptr;
};
