// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
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

	isLooking = false;

	rotate_speed = 5.0f;

	move_speed = 0.5f;
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

void AEnemyCharacter::Move(float Deltatime)
{

	float distance = FVector::Dist(player_actor->GetActorLocation(), my_pawn->GetActorLocation());

	if (distance < stop_distance)
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
	if (!my_pawn && !player_actor) return;

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

}
