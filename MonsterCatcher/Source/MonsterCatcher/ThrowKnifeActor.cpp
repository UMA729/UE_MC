// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowKnifeActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AThrowKnifeActor::AThrowKnifeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KunaiCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShereComp"));
	KunaiCollision->InitSphereRadius(5.0f);
	KunaiCollision->BodyInstance.SetCollisionProfileName("Projectile");
	KunaiCollision->OnComponentHit.AddDynamic(this, &AThrowKnifeActor::OnHit);

	KunaiCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));

	RootComponent = KunaiCollision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = KunaiCollision;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->
}

void AThrowKnifeActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}
