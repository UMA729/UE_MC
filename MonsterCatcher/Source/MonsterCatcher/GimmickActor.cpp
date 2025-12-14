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
// BeginPlay
void AGimmickActor::BeginPlay()
{
    Super::BeginPlay();

    if (Gimmick)
    {
        ButtonStartLocation = Gimmick->GetActorLocation();
        Gimmick->SetActorHiddenInGame(true);
        Gimmick->SetActorEnableCollision(false);
        Gimmick->SetActorTickEnabled(false);
    }

    EnemyStartLocations.Empty();
    EnemyStartLocations.Reserve(EnemyActors.Num());
    for (AActor* Enemy : EnemyActors)
    {
        if (!Enemy) continue;

        EnemyStartLocations.Add(Enemy->GetActorLocation());

        Enemy->SetActorHiddenInGame(true);
        Enemy->SetActorEnableCollision(false);
        Enemy->SetActorTickEnabled(false);
    }
}



void AGimmickActor::Emerge()
{
	if (Gimmick)
	{
		Gimmick->SetActorHiddenInGame(false);
		Gimmick->SetActorEnableCollision(true);
		Gimmick->SetActorTickEnabled(true);
	}

    for (int32 i = 0; i < EnemyActors.Num(); ++i)
    {
        AActor* Enemy = EnemyActors[i];
        if (!Enemy) continue;

        Enemy->SetActorLocation(EnemyStartLocations[i]);
        Enemy->SetActorHiddenInGame(false);
        Enemy->SetActorEnableCollision(true);
        Enemy->SetActorTickEnabled(true);
    }

}


// Called every frame
void AGimmickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}