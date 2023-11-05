// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LestaGameJam/CoreTypes.h"
#include "JmHud.generated.h"


UCLASS()
class LESTAGAMEJAM_API AJMHUD : public AHUD
{
	GENERATED_BODY()
public:
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;
private:
	UPROPERTY()
	TMap<EMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr; 
    
	void OnMatchStateChanged(EMatchState State);
};
