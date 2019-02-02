// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankPlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("The player controller is not possessing the tank!!!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("The player controller is possessing %s!!!"), *(ControlledTank->GetName()))
	}
}

void AMyTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		AimTowardsCrossHair();
}

void AMyTankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation)) { // Going to LineTrace
		GetControlledTank()->AimAt(HitLocation); // Tell the controlled tank what to do when the line trace hit the object
	}
}
// Get the line trace through the cross hair, return true if hits landscape
bool AMyTankPlayerController::GetSightRayHitLocation (FVector& HitLocation) const
{
	//Finding the crosshair position
		// Size of the current viewport
	int32 ViewportSizeX, ViewportSizeY; 
	GetViewportSize(ViewportSizeX, ViewportSizeY);
		// Getting the Location of the crosshair
	auto ScreenLocation = FVector2D ((CrossHairXLocation*ViewportSizeX), (CrossHairYLocation*ViewportSizeY));
	//De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
		//Linetrace along that direction, and see what we hit (up to max range)
	}
	return true;
}
bool AMyTankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection* LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation,
		EndLocation, 
		ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}
bool AMyTankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

ATank* AMyTankPlayerController::GetControlledTank() const {
	
	return Cast<ATank> (GetPawn());
}




