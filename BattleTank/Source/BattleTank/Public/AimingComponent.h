// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

class UTankBarrel;
class UTurret;
UENUM()
enum class EFiringStatus: uint8 {
	Locked,
	Aiming,
	Reloading
};
//  Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void Initialize(UTankBarrel *BarrelToSet, UTurret* TurretToSet);

	
	
protected: // In order for the subclass "Tank Aiming Component BP" to access the variable
			// from blueprint
	UPROPERTY (BlueprintReadOnly, Category = "Variables")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
	
private:
	UTankBarrel* Barrel = nullptr;  
	void MoveBarrel(FVector AimDirection);
	
	UTurret* Turret = nullptr;
	
};
