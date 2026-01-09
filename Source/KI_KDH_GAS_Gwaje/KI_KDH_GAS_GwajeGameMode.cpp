// Copyright Epic Games, Inc. All Rights Reserved.

#include "KI_KDH_GAS_GwajeGameMode.h"
#include "KI_KDH_GAS_GwajeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKI_KDH_GAS_GwajeGameMode::AKI_KDH_GAS_GwajeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
