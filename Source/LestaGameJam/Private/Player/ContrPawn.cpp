// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ContrPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AContrPawn::AContrPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	m_springArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	m_springArmComponent->SetupAttachment(SceneComponent);
	
	m_cameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	m_cameraComponent->SetupAttachment(m_springArmComponent);

}

// Called every frame
void AContrPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


