// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"
class AProjectile;
class UTankBarrel;
class UTurret;
UENUM()
enum class EFiringStatus: uint8 {
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

//  Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, 
		enum ELevelTick TickType, 
		FActorComponentTickFunction *ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	void MoveBarrel(FVector AimDirection);

	bool IsBarrelMoving();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Movement)
	void Initialize(UTankBarrel *BarrelToSet, UTurret* TurretToSet);
	
	EFiringStatus GetFiringStatus() const;
protected: // In order for the subclass "Tank Aiming Component BP" to access the variable
			// from blueprint
	UPROPERTY (BlueprintReadOnly, Category = "Variables")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;  
	
	UTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSecond = 3;

	double LastTimeFire = 1;

	FVector AimDirection ;

	int NoOfRounds = 10;
	
};
