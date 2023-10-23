// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_DeathTrigger.h"
#include "Components/BoxComponent.h"
#include "HTL_Characters/HTL_Player.h"


AHTL_DeathTrigger::AHTL_DeathTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = DeathTrigger;
}

void AHTL_DeathTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AHTL_Player* Player = Cast<AHTL_Player>(OtherActor))
	{
		Player->PlayerDied();
	}
}

void AHTL_DeathTrigger::BeginPlay()
{
	Super::BeginPlay();

	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &AHTL_DeathTrigger::OnOverlapBegin);
}
