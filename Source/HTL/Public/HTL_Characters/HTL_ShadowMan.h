// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HTL_ShadowMan.generated.h"

UCLASS()
class HTL_API AHTL_ShadowMan : public ACharacter
{
	GENERATED_BODY()

public:
	AHTL_ShadowMan();

	void StartDeathTimer(float Delay);

	UFUNCTION()
	void KillFunction();

protected:
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
};
