// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyTankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMyTankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	
	
};
