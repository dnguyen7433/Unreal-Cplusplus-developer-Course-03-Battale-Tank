// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class UAimingComponent;
class UTankBarrel;
class UTurret;
class AProjectile;
class UTankMovementComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();
protected:
	UAimingComponent* AimingComponent = nullptr;
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; 

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimePerSecond = 3;

	double LastTimeFire = 1;
	
	UTankBarrel* Barrel = nullptr; // TODO Remove it
};
