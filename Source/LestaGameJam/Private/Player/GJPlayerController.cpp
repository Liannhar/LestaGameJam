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
	InputComponent->BindAction("EndRound", IE_Pressed,this, &AGJPlayerController::EndRound);
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
	Camera->SetRelativeLocation(FVector(-1000.0f,0.0f,0.0f));
	if(GetWorld()) 
	{
		const auto GameMode = Cast<ALestaGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this,&AGJPlayerController::OnMatchStateChanged);
			GameMode->OnPassivePhase.AddDynamic(this,&AGJPlayerController::EnabInput);
			SetInputMode(FInputModeGameAndUI());
		}
	}
}

void AGJPlayerController::MoveRight(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto SpringArmComponent = ContrPawn->GetSpringArm();
	UE_LOG(LogTemp,Display,TEXT("Location %f"),SpringArmComponent->GetRelativeLocation().Y);
	UE_LOG(LogTemp,Display,TEXT("Amount %f"),Amount);
	if(!SpringArmComponent || (SpringArmComponent->GetRelativeLocation().Y>m_lengthYUpLimit && Amount>0.0f) || (SpringArmComponent->GetRelativeLocation().Y<m_lengthYDownLimit && Amount<0.0f)) return;
	SpringArmComponent->SetRelativeLocation(SpringArmComponent->GetRelativeLocation()+FVector(0.0f,Amount*m_cameraSpeed,0.0f));
}

void AGJPlayerController::MoveForward(float Amount)
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto SpringArmComponent = ContrPawn->GetSpringArm();
	
	
	if(!SpringArmComponent || (SpringArmComponent->GetRelativeLocation().X>m_lengthXUpLimit && Amount>0.0f) || (SpringArmComponent->GetRelativeLocation().X<m_lengthXDownLimit && Amount<0.0f)) return;
	SpringArmComponent->SetRelativeLocation(SpringArmComponent->GetRelativeLocation()+FVector(Amount*m_cameraSpeed,0.0f,0.0f));
}

void AGJPlayerController::Zoom(float Amount)
{
	
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	if(!Camera) return;
	if ((Camera->GetRelativeLocation().X>m_zoomDownLimit && Amount>=0.0f) || (Camera->GetRelativeLocation().X<m_zoomUPLimit && Amount<0.0f)) return;
	Camera->SetRelativeLocation(Camera->GetRelativeLocation()+FVector(Amount*m_zoomSpeed,0.0f,0.0f));
	
}

void AGJPlayerController::ToCharacter()
{
	if (!GetPawn()) return;
	const auto ContrPawn = Cast<AContrPawn>(GetPawn());
	if(!ContrPawn) return;
	const auto Camera = ContrPawn->GetCamera();
	const auto SpringArmComponent = ContrPawn->GetSpringArm();
	if(!Camera || !SpringArmComponent) return;
	Camera->SetRelativeLocation(FVector(-1000.0f,0.0f,0.0f));
	SpringArmComponent->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
	SpringArmComponent->SocketOffset.Z=m_socketCameraOffsetBaseZ;
	SpringArmComponent->SocketOffset.X=m_socketCameraOffsetBaseX;
	SpringArmComponent->SocketOffset.Y=m_socketCameraOffsetBaseY;
}

void AGJPlayerController::EndRound()
{
	if(GetWorld())
	{
		if(const auto GameMode = Cast<ALestaGameJamGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->EndPassivePhase();
			ToCharacter();
			DisableInput(this);
		}
	}
}

void AGJPlayerController::PauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
	const auto GameMode = Cast<ALestaGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
	//GameMode->GameOver();
}

void AGJPlayerController::EnabInput()
{
	EnableInput(this);
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
