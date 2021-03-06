// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup") 
	float AcceptanceRadius = 8000;
private:
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	//Get called when AI tank controller is possesesed
	
	virtual void Tick(float DeltaTime) override;
	// How close the AI tank can get to the player tank
	
};
