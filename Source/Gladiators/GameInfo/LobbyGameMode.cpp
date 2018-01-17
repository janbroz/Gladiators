// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "Players/LobbyPlayerController.h"
#include "Players/GladiatorPlayer.h"


ALobbyGameMode::ALobbyGameMode()
{
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
	DefaultPawnClass = AGladiatorPlayer::StaticClass();
}