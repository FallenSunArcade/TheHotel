// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HTL_PauseMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContinueDelegate);

class UButton;

UCLASS()
class HTL_API UHTL_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	FContinueDelegate ContinueDelegate;
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void StartButtonClicked();
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton = nullptr;
};
