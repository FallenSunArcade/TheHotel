// Copyright Epic Games, Inc. All Rights Reserved.

#include "HTLGameMode.h"
#include "HTLCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHTLGameMode::AHTLGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
