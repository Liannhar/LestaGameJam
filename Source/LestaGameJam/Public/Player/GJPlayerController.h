// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LestaGameJam/CoreTypes.h"
#include "GJPlayerController.generated.h"

class UCameraComponent;

UCLASS()
class LESTAGAMEJAM_API AGJPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_cameraSpeed = 10.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_zoomSpeed =50.0f;
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthXRightLimit=300.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthXLeftLimit=-300.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthYUpLimit=300.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthYDownLimit=-300.0f;*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthZoomDownLimit=120.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthZoomUpLimit=1000.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_socketCameraOffsetBaseZ=150.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_socketCameraOffsetBaseX=-450.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_socketCameraOffsetBaseY=0.0f;

protected:
	void OnMatchStateChanged(EMatchState MatchState);
	virtual void BeginPlay() override;
private:
	void MoveRight(float Amount);
	void MoveForward(float Amount);
	void Zoom(float Amount);
	void ToCharacter();
	void EndRound();
	void PauseGame();
	void EnabInput();
};
