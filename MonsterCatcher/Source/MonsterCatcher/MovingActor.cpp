// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	// ƒvƒŒƒCƒ„[‚ðæ‚¹‚Ä‚àŠŠ‚ç‚È‚¢‚æ‚¤‚É‚·‚é
	PlatformMesh->SetMobility(EComponentMobility::Movable);
	PlatformMesh->SetSimulatePhysics(false);
	PlatformMesh->SetEnableGravity(false);

}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = StartLocation + MoveOffset;

	// ˆÚ“®•ûŒü”»’è
	if (bGoingForward)
	{
		FVector MoveDir = (MoveOffset).GetSafeNormal();
		CurrentLocation += MoveDir * MoveSpeed * DeltaTime;

		if (FVector::Dist(CurrentLocation, StartLocation) >= MoveOffset.Size())
		{
			CurrentLocation = TargetLocation;
			bGoingForward = false;
		}
	}
	else
	{
		FVector MoveDir = (-MoveOffset).GetSafeNormal();
		CurrentLocation += MoveDir * MoveSpeed * DeltaTime;

		if (FVector::Dist(CurrentLocation, TargetLocation) >= MoveOffset.Size())
		{
			CurrentLocation = StartLocation;
			bGoingForward = true;
		}
	}

	SetActorLocation(CurrentLocation);

}

