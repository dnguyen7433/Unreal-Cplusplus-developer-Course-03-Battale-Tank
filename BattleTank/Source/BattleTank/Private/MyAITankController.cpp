// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAITankController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void AMyAITankController::BeginPlay()
{
	Super::BeginPlay();
	auto AIControlledTank = GetAIControlledTank();
	if (!AIControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing tank!!!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s!!!"), *(AIControlledTank ->GetName()))
	}
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController couldn't find the player's tank!!!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found: %s!!!"), *(PlayerTank->GetName()))
	}
}

void AMyAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetAIControlledTank()) { return; }
	if (!GetPlayerTank()) { return; }
	GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank * AMyAITankController::GetAIControlledTank() const

{
	auto AIControlledTank = Cast<ATank>(GetPawn());
	if (!AIControlledTank) {
		return nullptr;
	}
	else {
		return AIControlledTank;
	}
}

ATank * AMyAITankController::GetPlayerTank() const
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) {
		return nullptr;
	}
	else {
		return  PlayerTank;
	}
}
