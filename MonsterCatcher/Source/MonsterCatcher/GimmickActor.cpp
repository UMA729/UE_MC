// Fill out your copyright notice in the Description page of Project Settings.


#include "GimmickActor.h"
#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
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

        if (AEnemyCharacter* enemy_class = Cast<AEnemyCharacter>(Enemy))
        {
            enemy_class->bisSpawn = false;
            enemy_class->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }

        EnemyStartLocations.Add(Enemy->GetActorLocation());
        
        Enemy->SetActorHiddenInGame(true);
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

        if (AEnemyCharacter* enemy_class = Cast<AEnemyCharacter>(Enemy))
        {
            enemy_class->bisSpawn = true;
            enemy_class->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        }

        Enemy->SetActorHiddenInGame(false);

    }

}


// Called every frame
void AGimmickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}