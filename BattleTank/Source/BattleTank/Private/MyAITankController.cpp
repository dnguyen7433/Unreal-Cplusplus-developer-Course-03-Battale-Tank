// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAITankController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void AMyAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AIControlledTank = Cast<ATank>(GetPawn());
	if (!AIControlledTank) { return; }

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) { return; }

	AIControlledTank->AimAt(PlayerTank->GetActorLocation());
	AIControlledTank->Fire(); // TODO Every reload time per second
}




