// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "EnemyCharacter.generated.h"

class USphereComponent;

UCLASS()
class MONSTERCATCHER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float attack_radius;
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float stop_distance;

	//敵：ハイエナ
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool isHyena;
	//敵：始祖鳥
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool isArcheop;
	//敵：飛行キャラ（未定）
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool isFly_enemy;

	
	// Sets default values for this character's properties

protected:
	// Called when the game starts or when spawned

private:
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//攻撃フラグ
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool bisAttacking;
	//飛行フラグ
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool bisFlying;

	/** 接触判定用のCollision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;
	//移動速度
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float move_speed;
	//攻撃クールダウン
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float cooldown_time;
	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float attck_damage;
public:	
	APawn* my_pawn;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float Deltatime);

	//ハイエナ挙動
	void Hyena();
	//始祖鳥挙動
	void Archeop();
	//飛行キャラ挙動
	void FlyEnemy();
	//敵：ダッシュ
	void Dash();
	//敵：攻撃
	void Attack();
	//敵：攻撃ストップ
	void ResetAttack();

	float rotate_speed;

	bool isLooking;
	bool isRush;

	FTimerHandle attack_cooldown;

	AActor*player_actor;

};
