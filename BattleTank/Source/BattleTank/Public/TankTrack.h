// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track is used to set maximum driving forces, and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Set a throttle between -1 and + 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottles(float RelativeSpeed);
	// Setting Max forces in Newton, force = mass * acceleration
	UPROPERTY(EditDefaultsOnly, Category = Forces)
	float TrackMaxDrivingForce = 400000; // Assume 40 tonnes tank and 1 g (10m/s^2) acceleration)
	
};