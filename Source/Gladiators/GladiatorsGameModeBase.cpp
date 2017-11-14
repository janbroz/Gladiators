// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorsGameModeBase.h"
#include "Players/GladiatorPlayer.h"
#include "Players/GladiatorController.h"

AGladiatorsGameModeBase::AGladiatorsGameModeBase()
{
	DefaultPawnClass = AGladiatorPlayer::StaticClass();
	PlayerControllerClass = AGladiatorController::StaticClass();
}
