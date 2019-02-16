// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAITankController.h"
#include "AimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void AMyAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// NO NEED to cast to a tank because Tank is a pawn
	auto AIControlledTank = GetPawn();
	if (!ensure(AIControlledTank)) { return; }

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank)) { return; }
	// No need to hash include for MovementComponent because (MoveToActor) AIController and 
	// (RequestDirectMove)Nav Movement Component are linked in the Parent Classes already
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius in cemtimeter

	auto AimingComponent = AIControlledTank->FindComponentByClass<UAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire(); // TODO Every reload time per second
}




