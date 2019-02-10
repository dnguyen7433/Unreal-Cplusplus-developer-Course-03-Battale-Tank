// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public: 
	void Elevate(float RelativeSpeed); 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreePerSecond = 5;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegree = 40;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDegree = 0;
};
