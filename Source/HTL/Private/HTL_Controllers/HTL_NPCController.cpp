// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_NPCController.h"

#include "BehaviorTree/BlackboardComponent.h"


void AHTL_NPCController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AHTL_NPCController::SetPatrolPoint(const FVector& Point)
{
	GetBlackboardComponent()->SetValueAsVector("PatrolPoint", Point);
}

