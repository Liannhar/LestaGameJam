// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJPlayerController.h"

#include "Camera/CameraComponent.h"
#include "LestaGameJam/LestaGameJamGameModeBase.h"
#include "Player/ContrPawn.h"



void AGJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("CameraMoveRight", this, &AGJPlayerController::MoveRight);
	InputComponent->BindAxis("CameraMoveForward", this, &AGJPlayerController::MoveForward);
	InputComponent->BindAxis("CameraZoom", this, &AGJPlayerController::Zoom);
	InputComponent->BindAction("ToCharacter", IE_Pressed,this, &AGJPlayerController::ToCharacter);
	InputComponent->BindAction("Pause", IE_Pressed,this, &AGJPlayerController::PauseGame);
	bShowMouseCursor=true;
}

void AGJPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	//Camera->SetRelativeLocation(FVector(ContrPawn->GetActorLocation().X-300.0f,ContrPawn->GetActorLocation().Y,1000.0f));
	//Camera->SetRelativeRotation(FRotator(-60.0f,0.0f ,0.0f));
	if(GetWorld()) 
	{
		const auto GameMode = Cast<ALestaGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this,&AGJPlayerController::OnMatchStateChanged);
			GameMode->OnActivePhase.AddDynamic(this,&AGJPlayerController::ToCharacter);
			SetInputMode(FInputModeGameAndUI());
		}
	}
}

void AGJPlayerController::MoveRight(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	if ((Camera->GetRelativeLocation().Y>m_lengthYUpLimit && Amount>=0.0f) || (Camera->GetRelativeLocation().Y<m_lengthYDownLimit && Amount<0.0f)) return;
	Camera->SetRelativeLocation(Camera->GetRelativeLocation()+FVector(0.0f,Amount*m_cameraSpeed,0.0f));
}

void AGJPlayerController::MoveForward(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	if ((Camera->GetComponentLocation().X>m_lengthXUpLimit && Amount>=0.0f) || (Camera->GetComponentLocation().X<m_lengthXDownLimit && Amount<0.0f)) return;
	Camera->SetWorldLocation(Camera->GetComponentLocation()+FVector(Amount*m_cameraSpeed,0.0f,0.0f));
}

void AGJPlayerController::Zoom(float Amount)
{
	
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	//if ((Camera->GetRelativeLocation().X<m_zoomDownLimit && Amount<=0.0f) || (Camera->GetRelativeLocation().X>m_zoomUPLimit && Amount>0.0f)) return;
	Camera->SetWorldLocation(Camera->GetRelativeLocation()+FVector(Amount*m_zoomSpeed,0.0f,0.0f));
}

void AGJPlayerController::ToCharacter()
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	Camera->SetRelativeLocation(FVector(ContrPawn->GetActorLocation().X-300.0f,ContrPawn->GetActorLocation().Y,1000.0f));
}

void AGJPlayerController::ToBackCharacter()
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	Camera->SetRelativeLocation(FVector(ContrPawn->GetActorLocation().X-300.0f,ContrPawn->GetActorLocation().Y,1000.0f));
}


void AGJPlayerController::PauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
	const auto GameMode = Cast<ALestaGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
}

void AGJPlayerController::OnMatchStateChanged(EMatchState MatchState)
{
	if(MatchState == EMatchState::InProgress)
	{
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
	}
}
