// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "ContrPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LESTAGAMEJAM_API AContrPawn : public APawn
{
	GENERATED_BODY()

public:
	AContrPawn();

protected:
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Components")
	UCameraComponent* m_cameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USpringArmComponent* m_springArmComponent;

public:	
	virtual void Tick(float DeltaTime) override;
	UCameraComponent* GetCamera() const {return m_cameraComponent;}
	USpringArmComponent* GetSpringArm() const {return m_springArmComponent;}
};
