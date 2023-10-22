// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_BTTasks/HTL_WonderTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UHTL_WonderTask::UHTL_WonderTask()
{
	NodeName = TEXT("Wonder");
}

EBTNodeResult::Type UHTL_WonderTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	

	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		UNavigationSystemV1* Nav = UNavigationSystemV1::GetCurrent(GetWorld());
		FNavLocation wonderLocation;

		if (Nav->GetRandomReachablePointInRadius(OwnerComp.GetOwner()->GetActorLocation(), 500.f, wonderLocation))
		{
			Controller->GetBlackboardComponent()->SetValueAsVector("WonderLocation", wonderLocation.Location);
			return EBTNodeResult::Succeeded;
		}

	}

	return EBTNodeResult::Failed;
}
