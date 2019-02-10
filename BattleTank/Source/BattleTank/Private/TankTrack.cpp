// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottles(float RelativeSpeed) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttles at: %f"), *Name, RelativeSpeed)

		// TODO Clamp actual throttle value so players can't change too much

	auto ForceApplied = GetForwardVector()*RelativeSpeed*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

