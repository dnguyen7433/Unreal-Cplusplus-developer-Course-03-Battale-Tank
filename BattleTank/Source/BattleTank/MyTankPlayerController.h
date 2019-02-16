// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyTankPlayerController.generated.h"

/**
 * Responsible for helping players to aim.
 */
class ATank;
class UAimingComponent;
UCLASS()
class BATTLETANK_API AMyTankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrossHair();
	// Post: Moving the tank barrel so that a shot would hit the crosshair intersects the world
	bool GetSightRayHitLocation(FVector&) const; // Return true if the line trace hit the HitLocation

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;



	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UAimingComponent*  AimCompRef);
};
