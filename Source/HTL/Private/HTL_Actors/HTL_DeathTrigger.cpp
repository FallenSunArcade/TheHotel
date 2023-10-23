// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Actors/HTL_DeathTrigger.h"
#include "Components/BoxComponent.h"
#include "HTL_Characters/HTL_Player.h"
#include "HTL_GameInstances/HTL_GameInstance.h"
#include "Kismet/GameplayStatics.h"


AHTL_DeathTrigger::AHTL_DeathTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = DeathTrigger;
}

void AHTL_DeathTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UHTL_GameInstance* GameInstance = Cast<UHTL_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		GameInstance->SetWasEndingBad(true);
	}
	
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
