// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "GimmickWall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// RootComponent ÇçÏÇÈ
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = DefaultSceneRoot;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	Mesh->SetGenerateOverlapEvents(true);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ItemRatation = GetActorRotation();
	ItemRatation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(ItemRatation);

	FVector ItemLocation = StartLocation;
	float Time = GetWorld()->GetTimeSeconds();
	ItemLocation.Z += FMath::Sin(Time * FloatSpeed) * FloatAmplitude;
	SetActorLocation(ItemLocation);
}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapî≠ê∂!"));
	if (TargetWall) UE_LOG(LogTemp, Warning, TEXT("TargetWallÇ†ÇÈÇÊ"));

	if (TargetWall)
	{
		if (AGimmickWall* Wall = Cast<AGimmickWall>(TargetWall))
		{
			Wall->StartMoveUp();
		}
	}

	Destroy();
}