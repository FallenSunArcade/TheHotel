// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTL_SpawnTrigger.generated.h"

class UBoxComponent;
class AHTL_SpawnPoint;

UCLASS()
class HTL_API AHTL_SpawnTrigger : public AActor
{
	GENERATED_BODY()

public:
	AHTL_SpawnTrigger();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn Trigger")
	UBoxComponent* SpawnTrigger = nullptr;

	UPROPERTY(EditAnywhere, Category = "Spawn Trigger")
	AHTL_SpawnPoint* SpawnPoint = nullptr;
	
};
