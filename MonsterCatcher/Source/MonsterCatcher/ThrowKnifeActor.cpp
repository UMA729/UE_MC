// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowKnifeActor.h"
#include "EnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AThrowKnifeActor::AThrowKnifeActor()
{

	knife_collision = CreateDefaultSubobject<USphereComponent>(TEXT("ShereComp"));
	knife_collision->InitSphereRadius(10.0f);
	knife_collision->BodyInstance.SetCollisionProfileName("Projectile");
	knife_collision->OnComponentHit.AddDynamic(this, &AThrowKnifeActor::OnHit);		// set up a notification for when this component hits something blocking

	knife_collision->CanCharacterStepUpOn = ECB_No;

	RootComponent = knife_collision;

	projectile_movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	projectile_movement->UpdatedComponent = knife_collision;
	projectile_movement->InitialSpeed = 1500.f;
	projectile_movement->MaxSpeed = 1500.f;
	projectile_movement->bRotationFollowsVelocity = true;
	projectile_movement->bShouldBounce = false;

	knife_damage = 50.f;

	InitialLifeSpan = 3.0f;
}

void AThrowKnifeActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"),		*GetNameSafe(OtherActor));

	if (AEnemyCharacter* EnemyClass = Cast<AEnemyCharacter>(OtherActor))
	{
		EnemyClass->HP -= knife_damage;

		UE_LOG(LogTemp, Warning, TEXT("EnemyHit"));

		Destroy();
	}
}