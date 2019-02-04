// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "AimingComponent.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;

	PrimaryComponentTick.bCanEverTick = true; // TODO Should this really tick?


}


void UAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	
	if (!Barrel) { 
		UE_LOG(LogTemp, Warning, TEXT("Cannot find the barrel"))
		return;  
	}
	FVector OutLaunchVelocity(0.0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);
	if (bHaveAimSolution)

	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);

	}

	else
	{
		auto Time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);

	}

	// If no solution found do nothing
}
// Rotate the barrel according to the aim direction
void UAimingComponent::MoveBarrel(FVector AimDirection)
{
	//Work out the difference between the current barrel rotation and the aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

		// Move tank barrel
	Barrel->Elevate(5);
}

void UAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)

{
	Barrel = BarrelToSet;
}



