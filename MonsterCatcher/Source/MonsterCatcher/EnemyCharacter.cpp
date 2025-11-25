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

	RotateSpeed = 5.0f;

	MoveSpeed = 0.5f;
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
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, MoveSpeed);
	}


	if (!MyPawn && !PlayerActor) return;

	//プレイヤーとの距離をとる
	FVector TargetActor = PlayerActor->GetActorLocation() - MyPawn->GetActorLocation();
	//縦の追跡はなし
	TargetActor.Z = 0;

	FRotator LookatTarget = TargetActor.Rotation();
	FRotator CurrentMyRot = MyPawn->GetActorRotation();

	FRotator NewRotate = FMath::RInterpTo(
		CurrentMyRot,
		LookatTarget,
		Deltatime,
		RotateSpeed
	);


	//プレイヤーを見る
	MyPawn->SetActorRotation(NewRotate);

	
}

void AEnemyCharacter::Dash()
{
}

void AEnemyCharacter::Attack()
{

}
