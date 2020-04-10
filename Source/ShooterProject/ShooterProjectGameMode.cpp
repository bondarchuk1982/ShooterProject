// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShooterProjectGameMode.h"
#include "ShooterProjectHUD.h"
#include "ShooterProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterProjectGameMode::AShooterProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterProjectHUD::StaticClass();
}
