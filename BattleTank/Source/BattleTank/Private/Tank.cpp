// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "AimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Public/Tank.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
	// No need to protect the pointer in the constructor as it is constructed here
	TankAimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));


}

void ATank::AimAt(FVector HitLocation)
{	
	if (TankAimingComponent) {
		
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	if (!Barrel) { return; }
	bool IsReloaded = (FPlatformTime::Seconds() - LastTimeFire) > ReloadTimePerSecond;
	if (Barrel && IsReloaded) {
		// Otherwise, spawning the projectile at the socket position of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		if (!Projectile) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeFire = FPlatformTime::Seconds();
	}
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

