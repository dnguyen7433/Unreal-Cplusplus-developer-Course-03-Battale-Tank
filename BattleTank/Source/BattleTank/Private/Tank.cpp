// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "AimingComponent.h"


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
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

