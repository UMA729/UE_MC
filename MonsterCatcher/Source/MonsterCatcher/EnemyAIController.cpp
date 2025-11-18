// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"


#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"   

AEnemyAIController::AEnemyAIController()
{

	AIControl = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;

	AIControl->ConfigureSense(*SightConfig);
	AIControl->SetDominantSense(SightConfig->GetSenseImplementation());
}