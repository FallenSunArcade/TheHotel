// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_SpawnPoint.h"
#include "HTL_Characters/HTL_ShadowMan.h"
#include "HTL_Controllers/HTL_NPCController.h"

AHTL_SpawnPoint::AHTL_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHTL_SpawnPoint::Spawn()
{
	if (AHTL_ShadowMan* ShadowMan = GetWorld()->SpawnActor<AHTL_ShadowMan>(PawnClass, GetActorTransform()))
	{
		ShadowMan->StartDeathTimer(DeathDelay);
		
		if (AHTL_NPCController* NPCController = Cast<AHTL_NPCController>(ShadowMan->GetController()))
		{
			if (PatrolPoint)
			{
				NPCController->SetPatrolPoint(PatrolPoint->GetActorLocation());
				NPCController->SetMovementDelay(MovementDelay);
			}
		}
	}
}

void AHTL_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

