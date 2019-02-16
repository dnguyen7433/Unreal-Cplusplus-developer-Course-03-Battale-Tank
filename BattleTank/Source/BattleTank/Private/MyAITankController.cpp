// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAITankController.h"
#include "Tank.h"
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
	if (!ensure(AIControlledTank)) { return; }

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(PlayerTank)) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius in cemtimeter
	AIControlledTank->AimAt(PlayerTank->GetActorLocation());
	AIControlledTank->Fire(); // TODO Every reload time per second
}




