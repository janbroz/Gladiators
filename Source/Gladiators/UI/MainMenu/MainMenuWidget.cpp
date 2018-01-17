// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "GameInfo/GameInfoInstance.h"


UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInfoRef = Cast<UGameInfoInstance>(GetWorld()->GetGameInstance());
}