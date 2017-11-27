// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorsGameModeBase.h"
#include "Players/GladiatorPlayer.h"
#include "Players/GladiatorController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

AGladiatorsGameModeBase::AGladiatorsGameModeBase()
{
	ConstructorHelpers::FObjectFinder<UBlueprint> Character_BP(TEXT("/Game/Blueprints/Characters/Pan/Pan"));
	if (Character_BP.Object != NULL)
	{
		DefaultPawnClass = (UClass*)Character_BP.Object->GeneratedClass;
	}
	else
	{
		DefaultPawnClass = AGladiatorPlayer::StaticClass();
	}

	PlayerControllerClass = AGladiatorController::StaticClass();
}
