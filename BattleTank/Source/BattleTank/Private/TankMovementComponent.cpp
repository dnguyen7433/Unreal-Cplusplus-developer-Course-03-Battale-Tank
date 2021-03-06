// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, 
	UTankTrack* RightTrackToSet) {
	if (!ensure(LeftTrackToSet || RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
void UTankMovementComponent::IntendToMoveForward(float Throw)
{
	
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottles(Throw);
	RightTrack->SetThrottles(Throw);
	
}

void UTankMovementComponent::IntendToTurnRight(float Throw)
{
	
	if (!ensure(LeftTrack || RightTrack)) { return;  }
	
	LeftTrack->SetThrottles(Throw);
	RightTrack->SetThrottles(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	
	//No need to call Super as we are replacing the functionality
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct( AIForwardIntention, TankForwardDirection );
	IntendToMoveForward(ForwardThrow);
	
	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention) ;
	auto SteeringMagnitude = RightThrow.Size();
	if ((RightThrow.X) <= 0)
	IntendToTurnRight(- SteeringMagnitude);
	else {
		IntendToTurnRight(SteeringMagnitude);
	}
	
}

