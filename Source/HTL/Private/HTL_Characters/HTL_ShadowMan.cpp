// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Characters/HTL_ShadowMan.h"


// Sets default values
AHTL_ShadowMan::AHTL_ShadowMan()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHTL_ShadowMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHTL_ShadowMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHTL_ShadowMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

