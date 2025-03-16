// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_Unreal_1_GalvagnGameMode.h"
#include "CPP_Unreal_1_GalvagnCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPP_Unreal_1_GalvagnGameMode::ACPP_Unreal_1_GalvagnGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
