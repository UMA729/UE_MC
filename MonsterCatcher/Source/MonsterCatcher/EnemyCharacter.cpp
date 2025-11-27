// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	Sphere->SetupAttachment(GetCapsuleComponent());

	Sphere->SetSphereRadius(attack_radius);
	Sphere->SetActive(false);

	isLooking = false;
	bisFlying = false;
	cooldown_time = 1.0f;

	rotate_speed = 5.0f;

	move_speed = 0.5f;

	attck_damage = 10.0f;
}


// Called every frame  SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isLooking)
	{
		Move(DeltaTime);
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyCharacter* CharacterClass = Cast<AMyCharacter>(OtherActor))
	{

	}
}

void AEnemyCharacter::Move(float Deltatime)
{

	float distance = FVector::Dist(player_actor->GetActorLocation(), my_pawn->GetActorLocation());

	if (distance > stop_distance)
	{
		//ハイエナ挙動
		if (isHyena)
		{
			Hyena();
		}
		//始祖鳥挙動
		else if (isArcheop)
		{
			Archeop();
		}
		//飛行エネミー挙動
		else if (isFly_enemy)
		{
			FlyEnemy();
		}
	}
	else
	{
		Attack();
	}

	if (!my_pawn && !player_actor) return;

	//if (!isArcheop)
	{
		//プレイヤーとの距離をとる
		FVector TargetActor = player_actor->GetActorLocation() - my_pawn->GetActorLocation();
		//縦の追跡はなし
		TargetActor.Z = 0;

		FRotator LookatTarget = TargetActor.Rotation();
		FRotator CurrentMyRot = my_pawn->GetActorRotation();

		FRotator NewRotate = FMath::RInterpTo(
			CurrentMyRot,
			LookatTarget,
			Deltatime,
			rotate_speed
		);

		//プレイヤーを見る
		my_pawn->SetActorRotation(NewRotate);
	}
}

void AEnemyCharacter::Hyena()
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, move_speed);
	}
}

void AEnemyCharacter::Archeop()
{
	if (Controller != nullptr)
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, move_speed);

		if (!bisFlying)
		{

			FHitResult Hit;
			FVector Start = GetActorLocation();
			FVector End = Start - FVector(0, 0, 200); // 200cm下にRay

			FHitResult GroundHit;
			FCollisionQueryParams GroundParams;
			GroundParams.AddIgnoredActor(this);
			FCollisionObjectQueryParams  GrondObjParams;
			GrondObjParams.AddObjectTypesToQuery(ECC_GameTraceChannel3);

			bool bGround = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, GrondObjParams, GroundParams);

			if (!bGround)
			{
				bisFlying = true;
			}
			else
			{
				GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			}

		}
		else
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		}
	}
}

void AEnemyCharacter::FlyEnemy()
{

}

void AEnemyCharacter::Dash()
{

}

void AEnemyCharacter::Attack()
{
	if (!isFly_enemy && !bisAttacking)
	{
		bisAttacking = true;
		Sphere->SetActive(true);
	}
	else if (isFly_enemy && !bisAttacking)
	{
		//空中の敵の攻撃
		;
	}
	else
	{
		if(Sphere)
		Sphere->SetActive(false);

		GetWorld()->GetTimerManager().SetTimer(
			attack_cooldown,
			this,
			&AEnemyCharacter::ResetAttack,
			cooldown_time,
			false
		);
	}
}

void AEnemyCharacter::ResetAttack()
{
	bisAttacking = false;
}
