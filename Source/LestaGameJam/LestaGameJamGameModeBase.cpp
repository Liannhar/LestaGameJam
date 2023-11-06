// Copyright Epic Games, Inc. All Rights Reserved.


#include "LestaGameJamGameModeBase.h"

#include "EngineUtils.h"
#include "JmHud.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ContrPawn.h"
#include "Player/GJPlayerController.h"

ALestaGameJamGameModeBase::ALestaGameJamGameModeBase()
{
	DefaultPawnClass = AContrPawn::StaticClass();
	PlayerControllerClass = AGJPlayerController::StaticClass();
	HUDClass = AJMHUD::StaticClass();
}

void ALestaGameJamGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	m_currentRound=0;
}

void ALestaGameJamGameModeBase::EndPassivePhase()
{
	m_currentRound++;
	
	OnActivePhase.Broadcast();
}

void ALestaGameJamGameModeBase::StartPassivePhase()
{
	OnPassivePhase.Broadcast();
}

void ALestaGameJamGameModeBase::GameOver()
{
	for(auto Pawn:TActorRange<APawn>(GetWorld()))
	{
		if(Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(EMatchState::GameOver);
}


void ALestaGameJamGameModeBase::SetMatchState(EMatchState State)
{
	if(MatchState == State) return;
	
	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

void ALestaGameJamGameModeBase::Restart()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this,FName(CurrentLevelName));
}

bool ALestaGameJamGameModeBase::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if(PauseSet)
	{
		SetMatchState(EMatchState::Pause);
	}
	return PauseSet ;
}

bool ALestaGameJamGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if(PauseCleared)
	{
		SetMatchState(EMatchState::InProgress);
	}
	return PauseCleared;
}
