// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorController.h"


AGladiatorController::AGladiatorController()
{

}

void AGladiatorController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("HorizontalMovement", this, &AGladiatorController::MoveHorizontal);
	InputComponent->BindAxis("VerticalMovement", this, &AGladiatorController::MoveVertical);
}

void AGladiatorController::MoveHorizontal(float Amount)
{

}

void AGladiatorController::MoveVertical(float Amount)
{

}