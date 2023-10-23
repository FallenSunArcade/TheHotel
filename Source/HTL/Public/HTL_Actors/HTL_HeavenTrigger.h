// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTL_HeavenTrigger.generated.h"

class UBoxComponent;

UCLASS()
class HTL_API AHTL_HeavenTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHTL_HeavenTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
