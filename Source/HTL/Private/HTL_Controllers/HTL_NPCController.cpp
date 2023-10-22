// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_NPCController.h"


// Sets default values
AHTL_NPCController::AHTL_NPCController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHTL_NPCController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHTL_NPCController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

