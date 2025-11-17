// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UAIPerceptionComponent;
class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class MONSTERCATCHER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	//ìGÇÃAI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AICotrol;
	//ÉÇÉfÉãÉÅÉbÉVÉÖ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BulletMesh;
	//çUåÇÇÃîªíË
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	USphereComponent* AttackCollision;

public:
	// Sets default values for this character's properties

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	AEnemyCharacter();

	void Move();

	void Dash();

	void Attack();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
