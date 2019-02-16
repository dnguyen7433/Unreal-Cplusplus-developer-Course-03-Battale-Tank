// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
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
	
}
void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool IsReloaded = (FPlatformTime::Seconds() - LastTimeFire) > ReloadTimePerSecond;
	if (IsReloaded) {
		// Otherwise, spawning the projectile at the socket position of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeFire = FPlatformTime::Seconds();
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BeginPlay in Tank_BP
}




