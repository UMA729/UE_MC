// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class USphereComponent;

UCLASS()
class MONSTERCATCHER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float stop_distance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool isHyena;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool isArcheop;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool isFly_enemy;

public:
	AEnemyCharacter();
	// Sets default values for this character's properties

//protected:
	// Called when the game starts or when spawned

public:	
	APawn* my_pawn;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float Deltatime);

	void Hyena();

	void Archeop();

	void FlyEnemy();

	void Dash();

	void Attack();

	float rotate_speed;

	float move_speed;

	bool isLooking;

	bool isRush;

	AActor*player_actor;

};
