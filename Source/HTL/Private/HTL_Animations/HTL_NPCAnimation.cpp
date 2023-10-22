// Fill out your copyright notice in the Description page of Project Settings.


#include "HTL_Animations/HTL_NPCAnimation.h"


void UHTL_NPCAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	Pawn = TryGetPawnOwner();
}

void UHTL_NPCAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Pawn)
	{
		GroundSpeed = Pawn->GetVelocity().Length();
	}
}
