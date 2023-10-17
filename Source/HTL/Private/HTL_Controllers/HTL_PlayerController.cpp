// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_PlayerController.h"

AHTL_PlayerController::AHTL_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHTL_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
	FlushPressedKeys();
}
