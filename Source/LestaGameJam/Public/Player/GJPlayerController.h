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
	float m_cameraSpeed = 150.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_zoomSpeed =150.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_zoomUPLimit=-10000.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_zoomDownLimit=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthXUpLimit=70100.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthXDownLimit=-25800.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthYUpLimit=28380.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_lengthYDownLimit=-27800.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_socketCameraOffsetBaseZ=150.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_socketCameraOffsetBaseX=-450.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float m_socketCameraOffsetBaseY=0.0f;

	
protected:
	void OnMatchStateChanged(EMatchState MatchState);
	virtual void BeginPlay() override;
	
	void ToCharacter();

	UFUNCTION(BlueprintCallable	)
	void ToBackCharacter();

private:
	void MoveRight(float Amount);
	void MoveForward(float Amount);
	void Zoom(float Amount);
	void PauseGame();
};
