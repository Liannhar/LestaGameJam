// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JmHud.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "CoreTypes.h"
#include "LestaGameJam/LestaGameJamGameModeBase.h"

void AJMHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EMatchState::InProgress,CreateWidget<UUserWidget>(GetWorld(),PlayerHUDWidgetClass));
	GameWidgets.Add(EMatchState::Pause,CreateWidget<UUserWidget>(GetWorld(),PauseWidgetClass));
	GameWidgets.Add(EMatchState::GameOver,CreateWidget<UUserWidget>(GetWorld(),GameOverWidgetClass));

	for(const auto GameWidgetPair:GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if(!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GetWorld()) 
	{
		const auto GameMode = Cast<ALestaGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this,&AJMHUD::OnMatchStateChanged);
			GameWidgets[EMatchState::InProgress]->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AJMHUD::OnMatchStateChanged(EMatchState State)
{
	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
