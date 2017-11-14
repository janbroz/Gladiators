// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GladiatorController.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORS_API AGladiatorController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGladiatorController();
	
	// Lets override our control setup
	virtual void SetupInputComponent() override;

	// Character moves horizontally to his forward vector
	void MoveHorizontal(float Amount);

	// Character moves vertically to his forward vector
	void MoveVertical(float Amount);

};
