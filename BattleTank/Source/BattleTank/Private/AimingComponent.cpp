// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Public/CollisionQueryParams.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;


}
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// Make sure that AI Tank only fire after initial reload (3s)
	LastTimeFire =  GetWorld()->GetTimeSeconds();
}

void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (NoOfRounds <= 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	
	else if (((GetWorld()->GetTimeSeconds()) - LastTimeFire) < ReloadTimeInSecond){
		FiringStatus = EFiringStatus::Reloading;
		
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
		
	}
	else {
		
		FiringStatus = EFiringStatus::Locked;
	}
	
}



void UAimingComponent::AimAt(FVector HitLocation)
{
	
	if (!ensure(Barrel || Turret)) { return; }
	
	FVector OutLaunchVelocity(0.0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0
		,ESuggestProjVelocityTraceOption::DoNotTrace // Here is the bug if commented oout
		);
	if (bHaveAimSolution)

	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}

	
	// If no solution found do nothing
}
void UAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTurret * TurretToSet)
{
	if (!ensure(BarrelToSet || TurretToSet)) {return;}
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringStatus UAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int32 UAimingComponent::GetRoundsLeft() const
{
	return NoOfRounds;
}

// Rotate the barrel according to the aim direction
void UAimingComponent::MoveBarrel(FVector Target)
{
	if (!ensure(Barrel || Turret)) { return; }
	//Work out the difference between the current barrel rotation and the aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Target.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

		// Move tank barrel
	Barrel->Elevate(DeltaRotator.Pitch); 
	if (FMath::Abs(DeltaRotator.Yaw) <= 190) {
		Turret->Rotate(DeltaRotator.Yaw);
		
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
		
	}
	
}

bool UAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	//UE_LOG(LogTemp, Warning, TEXT("AimDirection: %s; BarrelForward: %s"),*(AimDirection.ToString()),
		//*(BarrelForward.ToString()))
	return !AimDirection.Equals(BarrelForward,0.1); // vectors are equal
	
}

void UAimingComponent::Fire()
{
	
	
	if (FiringStatus == EFiringStatus::Aiming || FiringStatus == EFiringStatus::Locked) {
		if (NoOfRounds > 0) {
			// Otherwise, spawning the projectile at the socket position of the barrel
			if (!ensure(Barrel)) { return; }
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile")));

			if (!ensure(Projectile)) { return; }
			Projectile->LaunchProjectile(LaunchSpeed);
			LastTimeFire = GetWorld()->GetTimeSeconds();
			NoOfRounds--;
		}
	}
}





