// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HTL_HudOverlay.generated.h"

class AHTL_Player;

UCLASS()
class HTL_API UHTL_HudOverlay : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeOnInitialized() override;
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	AHTL_Player* PlayerRef = nullptr;
};
