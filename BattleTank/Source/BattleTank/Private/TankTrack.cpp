// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();
	// Calculate and apply sideway (F = m * a)
	auto RootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce =( CorrectionAcceleration * (RootComponent->GetMass())) / 2;
	RootComponent->AddForce(CorrectionForce);
}

void UTankTrack::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottles(float RelativeSpeed) {
	
		// TODO Clamp actual throttle value so players can't change too much

	auto ForceApplied = GetForwardVector()*RelativeSpeed*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

