// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInfoInstance.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORS_API UGameInfoInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGameInfoInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		void CreateMainWidget();
	UFUNCTION()
		void ShowHostMenu();
	UFUNCTION()
		void ShowServerMenu();
	UFUNCTION()
		void ShowOptionsMenu();
	UFUNCTION()
		void LaunchLobby(int32 NumberOfPlayers, bool bEnableLan, FText NewServerName);
	UFUNCTION()
		void ShowLoadingScreen();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UMainMenuWidget> MainMenuClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		class UMainMenuWidget* MainMenuWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UHostMenuWidget> HostMenuClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		class UHostMenuWidget* HostMenuWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UServerMenuWidget> ServerMenuClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		class UServerMenuWidget* ServerMenuWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UOptionsMenuWidget> OptionsMenuClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		class UOptionsMenuWidget* OptionsMenuWidget;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	UPROPERTY(Replicated)
		int32 MaxPlayers;
	UPROPERTY(Replicated)
		FText ServerName;
};
