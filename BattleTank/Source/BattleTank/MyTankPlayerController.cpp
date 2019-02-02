// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankPlayerController.h"
#include "GameFramework/Controller.h"

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
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()))
			
				// TODO Tell the controlled tank to aim at this point
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
	//Linetrace along that direction, and see what we hit (up to max range)
	return true;
}

ATank* AMyTankPlayerController::GetControlledTank() const {
	
	return Cast<ATank> (GetPawn());
}




