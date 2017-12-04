// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInfoInstance.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "UI/MainMenu/MainMenuWidget.h"
#include "UI/MainMenu/HostMenuWidget.h"
#include "UI/MainMenu/ServerMenuWidget.h"
#include "UI/MainMenu/OptionsMenuWidget.h"
#include "UnrealNetwork.h"
#include "CoreOnline.h"

UGameInfoInstance::UGameInfoInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UClass> MainMenuBP(TEXT("/Game/UI/MainMenu/MainMenu.MainMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> HostMenuBP(TEXT("/Game/UI/MainMenu/HostMenu.HostMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> ServerMenuBP(TEXT("/Game/UI/MainMenu/ServerMenu.ServerMenu_C"));
	static ConstructorHelpers::FObjectFinder<UClass> OptionsMenuBP(TEXT("/Game/UI/MainMenu/OptionsMenu.OptionsMenu_C"));
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
		HostMenuWidget->AddToViewport();
	}
	else
	{
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

void UGameInfoInstance::LaunchLobby(int32 NumberOfPlayers, bool bEnableLan, FText NewServerName)
{
	MaxPlayers = NumberOfPlayers;
	ServerName = NewServerName;
	ShowLoadingScreen();

	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC) 
	{
		

	}
}

void UGameInfoInstance::ShowLoadingScreen()
{

}