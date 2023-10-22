// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_SpawnTrigger.h"
#include "Components/BoxComponent.h"
#include "HTL_Actors/HTL_SpawnPoint.h"
#include "HTL_Characters/HTL_Player.h"


AHTL_SpawnTrigger::AHTL_SpawnTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpawnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = SpawnTrigger;
}

void AHTL_SpawnTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AHTL_Player* Player = Cast<AHTL_Player>(OtherActor))
	{
		if(SpawnPoint)
		{
			SpawnPoint->Spawn();
		}
	}
}

void AHTL_SpawnTrigger::BeginPlay()
{
	Super::BeginPlay();

	SpawnTrigger->OnComponentBeginOverlap.AddDynamic(this, &AHTL_SpawnTrigger::OnOverlapBegin);
}

