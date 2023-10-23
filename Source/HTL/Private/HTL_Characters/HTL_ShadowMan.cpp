// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Characters/HTL_ShadowMan.h"


AHTL_ShadowMan::AHTL_ShadowMan()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHTL_ShadowMan::StartDeathTimer(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHTL_ShadowMan::KillFunction, Delay, false);
}

void AHTL_ShadowMan::KillFunction()
{
	Destroy();
}

void AHTL_ShadowMan::BeginPlay()
{
	Super::BeginPlay();
}

