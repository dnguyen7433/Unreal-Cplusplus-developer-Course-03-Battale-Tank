// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	
}



void UTankTrack::SidewayForce()
{
	auto SlippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
	// Calculate and apply sideway (F = m * a)
	auto RootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (CorrectionAcceleration * (RootComponent->GetMass())) / 2;
	RootComponent->AddForce(CorrectionForce);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnRegister()
{
	Super::OnRegister();
	
}
void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActors, UPrimitiveComponent * OtherComponents, FVector NormalImpulse, const FHitResult & Hit)
{
	// Note: Something funny happens here resulting into a bug in tank movement
	DriveTracks();
	CurrentThrottle = 0;
	SidewayForce();
	
}
void UTankTrack::SetThrottles(float RelativeSpeed) {
	CurrentThrottle = FMath::Clamp<float>(RelativeSpeed + CurrentThrottle, -1, 1);
	/*DriveTracks();
	SidewayForce();
	CurrentThrottle = 0;
	*/
}

void UTankTrack::DriveTracks()
{
	auto ForceApplied = GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
	
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}




