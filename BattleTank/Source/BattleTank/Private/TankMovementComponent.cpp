// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, 
	UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
void UTankMovementComponent::IntendToMoveForward(float Throw)
{
	
	LeftTrack->SetThrottles(Throw);
	RightTrack->SetThrottles(Throw);
	// TODO Prevent Double-Speed due to dual control
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we are replacing the functionality
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s move at speed : %s"), *Name, 
		*(MoveVelocity.ToString()))
	
}

