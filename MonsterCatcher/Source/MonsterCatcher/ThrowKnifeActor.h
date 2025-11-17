// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowKnifeActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MONSTERCATCHER_API AThrowKnifeActor : public AActor
{
	GENERATED_BODY()
	
	//“Š‚Ä‚«•ŠíƒƒbƒVƒ…
	UPROPERTY(VisibleAnywhere, Category = ThrowWeapon, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*KunaiMesh;
	//“Š‚Ä‚«•Ší“–‚½‚è”»’è
	UPROPERTY(VisibleAnywhere, Category = ThrowWeapon, meta = (AllowPrivateAccess = "true"))
	USphereComponent* KunaiCollision;
	//
	UPROPERTY(VisibleAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AThrowKnifeActor();

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	USphereComponent* GetCollisionComp()const { return KunaiCollision; }
	
	UProjectileMovementComponent* GetProjectileMovement()const { return ProjectileMovement; }
};
