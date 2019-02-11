// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAITankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMyAITankController : public AAIController
{
	GENERATED_BODY()
private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// How close the AI tank can get to the player tank
	float AcceptanceRadius = 3000;
};
