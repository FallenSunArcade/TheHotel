// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HTL_NPCController.generated.h"

class UBehaviorTree;

UCLASS()
class HTL_API AHTL_NPCController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetPatrolPoint(const FVector& Point);

private:
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree;

	FVector PatrolPoint;
};
