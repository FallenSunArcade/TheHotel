// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_SpawnPoint.h"


AHTL_SpawnPoint::AHTL_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHTL_SpawnPoint::Spawn()
{
	GetWorld()->SpawnActor<AActor>(ActorClass, GetActorTransform());
}

void AHTL_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

