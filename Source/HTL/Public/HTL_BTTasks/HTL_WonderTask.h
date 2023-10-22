// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "HTL_WonderTask.generated.h"

/**
 * 
 */
UCLASS()
class HTL_API UHTL_WonderTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UHTL_WonderTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
