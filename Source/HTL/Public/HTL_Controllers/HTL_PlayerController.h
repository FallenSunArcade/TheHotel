﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HTL_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HTL_API AHTL_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHTL_PlayerController();
	
protected:
	virtual void BeginPlay() override;
};
