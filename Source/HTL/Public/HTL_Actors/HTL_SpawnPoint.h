// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTL_SpawnPoint.generated.h"

UCLASS()
class HTL_API AHTL_SpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	AHTL_SpawnPoint();

	void Spawn();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	TSubclassOf<AActor> ActorClass;
};
