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
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()))
			
				// TODO Tell the controlled tank to aim at this point
	}
}
// Get the line trace through the cross hair, return true if hits landscape
bool AMyTankPlayerController::GetSightRayHitLocation (FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}

ATank* AMyTankPlayerController::GetControlledTank() const {
	
	return Cast<ATank> (GetPawn());
}



