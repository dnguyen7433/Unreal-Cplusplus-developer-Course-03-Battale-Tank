// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void UTurret::Rotate(float RotationSpeed) {
	auto Rotation = FMath::Clamp<int32>(RotationSpeed, -1, 1);
	auto RotationChange = Rotation * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRawRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator( 0, NewRawRotation, 0));
}


