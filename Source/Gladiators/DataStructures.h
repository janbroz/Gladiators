// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "DataStructures.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerInformation
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player information")
		FText PlayerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player information")
		UTexture2D* PlayerImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player information")
		class AGladiatorPlayer* Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player information")
		UTexture2D* CharacterImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player information")
		FText PlayerStatus;

	FPlayerInformation()
	{
		PlayerName = FText::FromString("None");
	}
};



class GLADIATORS_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
