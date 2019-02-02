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
	ATank* GetAIControlledTank() const;
	//Post: Possessing tanks that are not possessed by the player
	ATank* GetPlayerTank() const;
	//Post: Return the player's controlled tank with the purpose of aiming
};
