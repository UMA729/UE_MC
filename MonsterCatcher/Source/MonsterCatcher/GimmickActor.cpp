// Fill out your copyright notice in the Description page of Project Settings.


#include "GimmickActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGimmickActor::AGimmickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GimmickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

}

// Called when the game starts or when spawned
void AGimmickActor::BeginPlay()
{
	Super::BeginPlay();
	if (ButtonActor)
	{
		ButtonActor->SetActorHiddenInGame(true);
		ButtonActor->SetActorEnableCollision(false);
		ButtonActor->SetActorTickEnabled(false);
	}

	if (EnemyActor)
	{
		EnemyActor->SetActorHiddenInGame(true);
		EnemyActor->SetActorEnableCollision(false);
		EnemyActor->SetActorTickEnabled(false);
	}

}

// Called every frame
void AGimmickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGimmickActor::Emerge()
{
	if (ButtonActor)
	{
		ButtonActor->SetActorHiddenInGame(false);
		ButtonActor->SetActorEnableCollision(true);
		ButtonActor->SetActorTickEnabled(true);
	}

	if (EnemyActor)
	{
		EnemyActor->SetActorHiddenInGame(false);
		EnemyActor->SetActorEnableCollision(true);
		EnemyActor->SetActorTickEnabled(true);
	}

}

