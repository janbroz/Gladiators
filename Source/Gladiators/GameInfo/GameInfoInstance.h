// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UnrealNetwork.h"
#include "Online.h"
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

	UFUNCTION(BlueprintCallable)
		void CreateMainWidget();
	UFUNCTION(BlueprintCallable)
		void ShowHostMenu();
	UFUNCTION(BlueprintCallable)
		void ShowServerMenu();
	UFUNCTION(BlueprintCallable)
		void ShowOptionsMenu();
	void LaunchLobby(TSharedPtr<const FUniqueNetId> UserId, int32 NumberOfPlayers, bool bEnableLan, bool bIsPresence, FText NewServerName);
	void JoinServer(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, FOnlineSessionSearchResult &DesiredSession);

	void DestroySessionCaller(APlayerController PC);

	UFUNCTION()
		void ShowLoadingScreen();

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

public:
	// Delegate for when a session is created
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	// Delegate for when a session started
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class ULoadingScreenWidget> LoadingScreenClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widgets)
		class ULoadingScreenWidget* LoadingScreenWidget;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	UPROPERTY(Replicated)
		int32 MaxPlayers;
	UPROPERTY(Replicated)
		FText ServerName;
};
