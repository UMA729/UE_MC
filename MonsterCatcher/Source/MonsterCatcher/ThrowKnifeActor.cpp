// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowKnifeActor.h"
#include "EnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AThrowKnifeActor::AThrowKnifeActor()
{

	KunaiCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShereComp"));
	KunaiCollision->InitSphereRadius(5.0f);
	KunaiCollision->BodyInstance.SetCollisionProfileName("Projectile");
	KunaiCollision->OnComponentHit.AddDynamic(this, &AThrowKnifeActor::OnHit);		// set up a notification for when this component hits something blocking

	KunaiCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	KunaiCollision->CanCharacterStepUpOn = ECB_No;

	RootComponent = KunaiCollision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = KunaiCollision;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	//ProjectileMovement->

	knife_damage = 50.f;

	InitialLifeSpan = 3.0f;
}

void AThrowKnifeActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		if (AEnemyCharacter* EnemyClass = Cast<AEnemyCharacter>(OtherActor))
		{
			EnemyClass->HP -= knife_damage;
		}
		Destroy();
	}
}