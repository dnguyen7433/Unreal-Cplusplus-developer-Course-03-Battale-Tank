// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "TankProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/Actor.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Tank.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(Cast<USceneComponent>(CollisionMesh));
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActors, UPrimitiveComponent * OtherComponents, FVector NormalImpulse, const FHitResult & Hit)
{
	
	LaunchBlast->Deactivate();
	ImpactBlast->Activate(true);
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this, // who the damage start from?
		DamageAmount, // Damage amount
		GetActorLocation(), // where the damage starts from?
		ExplosionForce->Radius, // For radius of the damage
		UDamageType::StaticClass(),
		TArray<AActor*>() // Damage all actors
	);
		
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerExpired, DestroyDelay, false);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	if (!ensure(ProjectileMovement)) { return; }
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMovement->Activate(true);
}

void AProjectile::OnTimerExpired()
{
	 Destroy();
}


