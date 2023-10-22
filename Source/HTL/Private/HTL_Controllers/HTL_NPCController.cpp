// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Controllers/HTL_NPCController.h"


void AHTL_NPCController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
