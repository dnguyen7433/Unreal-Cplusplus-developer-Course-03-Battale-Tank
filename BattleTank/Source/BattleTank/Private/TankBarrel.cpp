// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame
	//Given a max elevation speed, and the frame time
	auto Speed = FMath::Clamp<int32>(RelativeSpeed, -1, 1);
	auto ElevationChange = Speed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRawElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(NewRawElevation, MinDegree, MaxDegree);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	
	
}
