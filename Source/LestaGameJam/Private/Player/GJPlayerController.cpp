// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJPlayerController.h"

#include "Camera/CameraComponent.h"
#include "Player/ContrPawn.h"


void AGJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("CameraMoveRight", this, &AGJPlayerController::MoveRight);
	InputComponent->BindAxis("CameraMoveForward", this, &AGJPlayerController::MoveForward);
	InputComponent->BindAxis("CameraZoom", this, &AGJPlayerController::Zoom);
	InputComponent->BindAction("ToCharacter", IE_Pressed,this, &AGJPlayerController::ToCharacter);
	InputComponent->BindAction("EndRound", IE_Pressed,this, &AGJPlayerController::EndRound);
}

void AGJPlayerController::MoveRight(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	//if((Camera->GetRelativeLocation().Y<m_lengthXRightLimit && Amount<0.0f) || (Camera->GetRelativeLocation().Y<m_lengthYDownLimit && Amount>0.0f)) return;
	Camera->SetRelativeLocation(Camera->GetRelativeLocation()+FVector(0.0f,Amount*m_cameraSpeed,0.0f));
}

void AGJPlayerController::MoveForward(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	//if ((Camera->GetRelativeLocation().X<m_lengthXRightLimit && Amount>0.0f) || (Camera->GetRelativeLocation().X<m_lengthXLeftLimit && Amount<0.0f)) return;
	Camera->SetRelativeLocation(Camera->GetRelativeLocation()+FVector(Amount*m_cameraSpeed,0.0f,0.0f));
}

void AGJPlayerController::Zoom(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto SpringArmComponent = ContrPawn->GetSpringArm();
	if(!SpringArmComponent || (SpringArmComponent->SocketOffset.Z<ContrPawn->GetActorLocation().Z+ m_lengthZoomDownLimit && Amount>0.0f) || (SpringArmComponent->SocketOffset.Z>ContrPawn->GetActorLocation().Z+ m_lengthZoomUpLimit && Amount<0.0f)) return;
	SpringArmComponent->SocketOffset.Z+=-Amount*m_zoomSpeed;
}

void AGJPlayerController::ToCharacter()
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	const auto SpringArmComponent = ContrPawn->GetSpringArm();
	if(!Camera || !SpringArmComponent) return;
	Camera->SetRelativeLocation(ContrPawn->GetActorLocation());
	SpringArmComponent->SocketOffset.Z=m_socketCameraOffsetBase;
	SpringArmComponent->TargetArmLength=10.0f;
}

void AGJPlayerController::EndRound()
{
}
