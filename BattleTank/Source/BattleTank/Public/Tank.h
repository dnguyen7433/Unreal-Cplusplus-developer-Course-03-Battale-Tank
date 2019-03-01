// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(Death);
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Return Current Health as Percentage of Starting Health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();
	
	// Will get called by the engine if it is in radial damage
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,AActor * DamageCauser) override; 
private:
	ATank();
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
};
