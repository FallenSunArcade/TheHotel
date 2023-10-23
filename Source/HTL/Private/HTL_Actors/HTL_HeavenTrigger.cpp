// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_HeavenTrigger.h"
#include "Components/BoxComponent.h"
#include "HTL_Characters/HTL_Player.h"
#include "HTL_GameInstances/HTL_GameInstance.h"
#include "Kismet/GameplayStatics.h"


AHTL_HeavenTrigger::AHTL_HeavenTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	HeavenTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = HeavenTrigger;
}

void AHTL_HeavenTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UHTL_GameInstance* GameInstance = Cast<UHTL_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		GameInstance->SetWasEndingBad(false);
	}
	
	if(AHTL_Player* Player = Cast<AHTL_Player>(OtherActor))
	{
		Player->PlayerDied(false);
	}
}

void AHTL_HeavenTrigger::BeginPlay()
{
	Super::BeginPlay();

	HeavenTrigger->OnComponentBeginOverlap.AddDynamic(this, &AHTL_HeavenTrigger::OnOverlapBegin);
}
