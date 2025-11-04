// Fill out your copyright notice in the Description page of Project Settings.


#include "GimmickWall.h"

// Sets default values
AGimmickWall::AGimmickWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	RootComponent = WallMesh;
}

// Called when the game starts or when spawned
void AGimmickWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGimmickWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		float MoveStep = MoveSpeed * DeltaTime;
		FVector WallLocation = GetActorLocation();
		WallLocation.Z += MoveStep;
		SetActorLocation(WallLocation);

		MoveSoFar += MoveStep;
		if (MoveSoFar >= MoveDistance)
		{
			isMoving = false;//è„è∏èIóπ
		}
	}
}

void AGimmickWall::StartMoveUp()
{
	isMoving = true;
	MoveSoFar = 0.f;
}