// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_HeavenTrigger.h"


// Sets default values
AHTL_HeavenTrigger::AHTL_HeavenTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHTL_HeavenTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHTL_HeavenTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

