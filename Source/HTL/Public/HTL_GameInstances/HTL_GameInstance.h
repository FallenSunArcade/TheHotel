// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HTL_GameInstance.generated.h"


UCLASS()
class HTL_API UHTL_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	bool GetWasEndingBad() const { return bWasEndBad; }

	void SetWasEndingBad(bool WasEndBad) { bWasEndBad = WasEndBad;}

private:
	UPROPERTY(EditAnywhere)
	bool bWasEndBad = true;
};
