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
	// Get the world location if the linetrace through the crosshair
	// If hit the landscape
		// Tell the controlled tank to aim at this point
}

ATank* AMyTankPlayerController::GetControlledTank() const {
	
	return Cast<ATank> (GetPawn());
}




