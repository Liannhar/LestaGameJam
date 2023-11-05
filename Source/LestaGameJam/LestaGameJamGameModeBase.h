// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoreTypes.h"
#include "LestaGameJamGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivePhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPassivePhase);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature,EMatchState);


UCLASS()
class LESTAGAMEJAM_API ALestaGameJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALestaGameJamGameModeBase();

public:
	UPROPERTY(BlueprintAssignable)
	FOnActivePhase OnActivePhase;
	UPROPERTY(BlueprintAssignable)
	FOnActivePhase OnPassivePhase;

	FOnMatchStateChangedSignature OnMatchStateChanged;
	
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentRound(){return m_currentRound;}
	UFUNCTION(BlueprintCallable)
	void StartPassivePhase();
	UFUNCTION(BlueprintCallable)
	void EndPassivePhase();
	UFUNCTION(BlueprintCallable)
	void Restart();
	UFUNCTION(BlueprintCallable)
	virtual bool ClearPause() override;
	UFUNCTION(BlueprintCallable)
	void GameOver();
	
protected:
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
	
	EMatchState MatchState = EMatchState::WaitingToStart;
	virtual void BeginPlay() override;

private:
	int32 m_currentRound = 0;
	void SetMatchState(EMatchState State);
};
