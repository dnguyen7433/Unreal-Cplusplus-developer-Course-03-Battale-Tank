// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Public/Tank.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	// No need to protect the pointer in the constructor as it is constructed here
	
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Tank is destroyed"))
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() {
	return ((float)CurrentHealth/(float)StartingHealth);
}