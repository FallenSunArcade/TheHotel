// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_DeathTrigger.h"
#include "Components/BoxComponent.h"


AHTL_DeathTrigger::AHTL_DeathTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = DeathTrigger;
}

void AHTL_DeathTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AHTL_DeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}
