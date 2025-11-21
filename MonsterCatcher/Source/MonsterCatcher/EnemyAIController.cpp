// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"   

AEnemyAIController::AEnemyAIController()
{

	PerceptionCmp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionCmp->ConfigureSense(*SightConfig);
	PerceptionCmp->SetDominantSense(SightConfig->GetSenseImplementation());

	islooking = false;

	RotateSpeed = 5.0f;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionCmp)
	{
		PerceptionCmp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
	}
}

void AEnemyAIController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	if (islooking)
	{
		APawn* ControlledPawn = GetPawn();
		if (!ControlledPawn&&!PlayerActor) return;

		//プレイヤーとの距離をとる
		FVector TargetActor = PlayerActor->GetActorLocation() - ControlledPawn->GetActorLocation();
		//縦の追跡はなし
		TargetActor.Z = 0;

		FRotator LookatTarget = TargetActor.Rotation();
		FRotator CurrentMyRot = ControlledPawn->GetActorRotation();

		FRotator NewRotate = FMath::RInterpTo(
			CurrentMyRot,
			LookatTarget,
			Deltatime,
			RotateSpeed
		);

			//プレイヤーを見る
		ControlledPawn->SetActorRotation(NewRotate);
		
	}
}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{

	if (Stimulus.WasSuccessfullySensed())
	{
		PlayerActor = Actor;

		islooking = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("leave：%s"), *Actor->GetName());

	}
}