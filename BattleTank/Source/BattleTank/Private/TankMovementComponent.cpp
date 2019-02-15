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

void UTankMovementComponent::IntendToTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return;  }
	UE_LOG(LogTemp, Warning, TEXT("Inside IntendToTurnRight"))
	LeftTrack->SetThrottles(Throw);
	RightTrack->SetThrottles(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	
	//No need to call Super as we are replacing the functionality
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	//, *(TankForwardDirection.ToString()))
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
	UE_LOG(LogTemp, Warning, TEXT("%f"), (SteeringMagnitude ))
}

