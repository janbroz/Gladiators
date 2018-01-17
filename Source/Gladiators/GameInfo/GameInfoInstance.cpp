// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInfoInstance.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "UI/MainMenu/MainMenuWidget.h"
#include "UI/MainMenu/HostMenuWidget.h"
#include "UI/MainMenu/ServerMenuWidget.h"
#include "UI/MainMenu/OptionsMenuWidget.h"
#include "UI/General/LoadingScreenWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UGameInfoInstance::UGameInfoInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UClass> MainMenuBP(TEXT("/Game/UI/MainMenu/MainMenu.MainMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> HostMenuBP(TEXT("/Game/UI/MainMenu/HostMenu.HostMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> ServerMenuBP(TEXT("/Game/UI/MainMenu/ServerMenu.ServerMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> OptionsMenuBP(TEXT("/Game/UI/MainMenu/OptionsMenu.OptionsMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> LoadingScreenBP(TEXT("/Game/UI/General/LoadingScreen.LoadingScreen_C"));
	if (MainMenuBP.Object)
	{
		MainMenuClass = MainMenuBP.Object;
	}
	if (HostMenuBP.Object)
	{
		HostMenuClass = HostMenuBP.Object;
	}
	if (ServerMenuBP.Object)
	{
		ServerMenuClass = ServerMenuBP.Object;
	}
	if (OptionsMenuBP.Object)
	{
		OptionsMenuClass = OptionsMenuBP.Object;
	}
	if (LoadingScreenBP.Object)
	{
		LoadingScreenClass = LoadingScreenBP.Object;
	}
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UGameInfoInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UGameInfoInstance::OnStartOnlineGameComplete);
}

void UGameInfoInstance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGameInfoInstance, MaxPlayers);
	DOREPLIFETIME(UGameInfoInstance, ServerName);
}

void UGameInfoInstance::CreateMainWidget()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}
	else
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetFirstLocalPlayerController(), MainMenuClass);
		if (!MainMenuWidget) return;
		MainMenuWidget->AddToViewport();
	}
}

void UGameInfoInstance::ShowHostMenu()
{
	if (HostMenuWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Does"));
		HostMenuWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Doesn't"));
		HostMenuWidget = CreateWidget<UHostMenuWidget>(GetFirstLocalPlayerController(), HostMenuClass);
		if (!HostMenuWidget) return;
		HostMenuWidget->AddToViewport();
	}
}

void UGameInfoInstance::ShowServerMenu()
{
	UServerMenuWidget* ServerMenu = CreateWidget<UServerMenuWidget>(GetFirstLocalPlayerController(), ServerMenuClass);
	if (!ServerMenu)return;
	ServerMenu->AddToViewport();
}

void UGameInfoInstance::ShowOptionsMenu()
{
	if (OptionsMenuWidget)
	{
		OptionsMenuWidget->AddToViewport();
	}
	else
	{
		OptionsMenuWidget = CreateWidget<UOptionsMenuWidget>(GetFirstLocalPlayerController(), OptionsMenuClass);
		if (!OptionsMenuWidget)return;
		OptionsMenuWidget->AddToViewport();
	}
}

void UGameInfoInstance::LaunchLobby(TSharedPtr<const FUniqueNetId> UserId, int32 NumberOfPlayers, bool bEnableLan, bool bIsPresence, FText NewServerName)
{
	MaxPlayers = NumberOfPlayers;
	ServerName = NewServerName;
	ShowLoadingScreen();

	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC) 
	{
		IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub)
		{
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid() && UserId.IsValid())
			{
				SessionSettings = MakeShareable(new FOnlineSessionSettings());

				SessionSettings->bIsLANMatch = bEnableLan;
				SessionSettings->bUsesPresence = bIsPresence;
				SessionSettings->NumPublicConnections = NumberOfPlayers;
				SessionSettings->NumPrivateConnections = 0;
				SessionSettings->bAllowInvites = true;
				SessionSettings->bAllowJoinInProgress = true;
				SessionSettings->bShouldAdvertise = true;
				SessionSettings->bAllowJoinViaPresence = true;
				SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
				SessionSettings->Set(SETTING_MAPNAME, FString("NewMap"), EOnlineDataAdvertisementType::ViaOnlineService);

				OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
				FName SName = FName(TEXT("session"));
				Sessions->CreateSession(*UserId, SName, *SessionSettings);
				//return Sessions->CreateSession(*UserId, FName(TEXT("Test session"), *SessionSettings);
			}

		}
	}
}

void UGameInfoInstance::ShowLoadingScreen()
{
	
	if (LoadingScreenWidget)
	{
		LoadingScreenWidget->AddToViewport();
	}
	else
	{
		LoadingScreenWidget = CreateWidget<ULoadingScreenWidget>(GetFirstLocalPlayerController(), LoadingScreenClass);
		if (!LoadingScreenWidget)return;
		LoadingScreenWidget->AddToViewport();
	}

}


void UGameInfoInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
				Sessions->StartSession(SessionName);
			}
		}
	}


}

void UGameInfoInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}

	if (bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "NewMap", true, "listen");
	}

}

void UGameInfoInstance::JoinServer(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, FOnlineSessionSearchResult& DesiredSession)
{
	ShowLoadingScreen();

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->JoinSession(*UserId, SessionName, DesiredSession);
		}
	}
}

void UGameInfoInstance::DestroySessionCaller(APlayerController PC)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			// Here we should call destroy session.
		}
	}
}