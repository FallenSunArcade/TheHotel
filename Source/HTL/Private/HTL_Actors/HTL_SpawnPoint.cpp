// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_SpawnPoint.h"
#include "HTL_Controllers/HTL_NPCController.h"

AHTL_SpawnPoint::AHTL_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHTL_SpawnPoint::Spawn()
{
	if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(PawnClass, GetActorTransform()))
	{
		if (AHTL_NPCController* NPCController = Cast<AHTL_NPCController>(Pawn->GetController()))
		{
			if (PatrolPoint)
			{
				NPCController->SetPatrolPoint(PatrolPoint->GetActorLocation());
			}
		}
	}
}

void AHTL_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

