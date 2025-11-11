// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyCharacter>PlayerBPClass(TEXT("/Game/BluePrints/Character/BP_MyCharacter"));

	if (PlayerBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerBPClass.Class;
		PlayerClass = PlayerBPClass.Class;

	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
	if (PlayerStart)
	{
		SpawnTransform = PlayerStart->GetActorTransform();
	}
}

void AMyGameModeBase::KillPlayer(AMyCharacter* Player)
{
	//Player‚ð”jŠü
	Player->Destroy();

	//Respawn‚ðs‚¤
	RespawnPlayer();
}

void AMyGameModeBase::RespawnPlayer()
{
	if (!PlayerClass) return;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	// BPƒNƒ‰ƒX‚©‚ç¶¬
	AMyCharacter* NewPlayer = GetWorld()->SpawnActor<AMyCharacter>(PlayerClass, SpawnTransform, SpawnInfo);
	if (NewPlayer)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->Possess(NewPlayer);
		}
	}
}