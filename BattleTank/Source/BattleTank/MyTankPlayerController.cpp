// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankPlayerController.h"
#include "GameFramework/Controller.h"

ATank* AMyTankPlayerController::GetControlledTank() const {
	
	return Cast<ATank> (GetPawn());
}

void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AMyTankPlayerController BeginPlay()!!!"))

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("The player controller is not possessing the tank!!!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("The player controller is possessing %s!!!"), *(ControlledTank->GetName()))
	}
}
