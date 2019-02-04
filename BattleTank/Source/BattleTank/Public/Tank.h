// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class UAimingComponent;
class UTankBarrel;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference (UTankBarrel* BarrelToSet);
protected:
	UAimingComponent* TankAimingComponent = nullptr;
private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 5000; // TODO Finding the sensible default value of launch speed
	
	
};
