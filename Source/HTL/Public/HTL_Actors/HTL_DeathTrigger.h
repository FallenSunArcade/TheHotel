// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTL_DeathTrigger.generated.h"

class UBoxComponent;

UCLASS()
class HTL_API AHTL_DeathTrigger : public AActor
{
	GENERATED_BODY()

public:
	AHTL_DeathTrigger();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Death Trigger")
	UBoxComponent* DeathTrigger = nullptr;
};
