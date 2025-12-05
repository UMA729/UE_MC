// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "MyCharacter.h"
#include "MyGameModeBase.h"
#include "EnemyAIController.h"
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
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnHitOverlap);

	Sphere->InitSphereRadius(80.f);

	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Sphere->SetupAttachment(GetMesh());

	Sphere->SetGenerateOverlapEvents(true);

	//デバッグ用
	//Sphere->SetHiddenInGame(false);             // ゲーム中に見える
	//Sphere->bHiddenInGame = false;              // 念のため
	//Sphere->SetVisibility(true);



	//Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	isLooking = false;
	bisFlying = false;
	cooldown_time = 1.0f;

	rotate_speed = 5.0f;

	move_speed = 0.5f;

	attack_damage = 10.0f;

	HP = 100.0f;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ori_pos = GetActorLocation();

	if (auto* Ctrl = Cast<AEnemyAIController>(GetController()))
	{
		Ctrl->SightConfig->SightRadius = SightRadius;
		Ctrl->SightConfig->LoseSightRadius = LoseSightRadius;
		Ctrl->SightConfig->PeripheralVisionAngleDegrees = SightAngle;

		Ctrl->PerceptionCmp->RequestStimuliListenerUpdate();
	}
}

// Called every frame  SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HP < 0)
	{
		Destroy();
	}

	if (isArcheop)
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
			GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		}
		else
		{
			bisFlying = false;
			GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		}
	}

	if (isLooking)
	{
		Move(DeltaTime);
	}
	else
	{
		if (!my_pawn) return;

		FVector TargetActor = ori_pos - my_pawn->GetActorLocation();

		FRotator LookatTarget = TargetActor.Rotation();
		FRotator CurrentMyRot = my_pawn->GetActorRotation();

		FRotator NewRotate = FMath::RInterpTo(
			CurrentMyRot,
			LookatTarget,
			DeltaTime,
			rotate_speed
		);

		//プレイヤーを見る
		my_pawn->SetActorRotation(NewRotate);

		if (TargetActor.Y < 0)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			AddMovementInput(ForwardDirection, move_speed);

		}
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Move(float Deltatime)
{
	if (!my_pawn && !player_actor) return;
	float distance = FVector::Dist(player_actor->GetActorLocation(), my_pawn->GetActorLocation());

	if (distance > stop_distance)
	{
		//ハイエナ挙動
		if (isHyena)
		{
			Hyena(Deltatime);
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


void AEnemyCharacter::Hyena(float Deltatime)
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

void AEnemyCharacter::Run()
{

}

void AEnemyCharacter::Attack()
{
	if (!isFly_enemy && !bisAttacking)
	{
		bisAttacking = true;
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			// クールタイム開始
			Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &AEnemyCharacter::OnAttackMontageEnded);

			AnimInstance->Montage_Play(AttackMontage);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
		}
	}
	else if (isFly_enemy && !bisAttacking)
	{
		//空中の敵の攻撃
		;
	}
}

void AEnemyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GetWorld()->GetTimerManager().SetTimer(
		timer_handle,
		this,
		&AEnemyCharacter::ResetAttack,
		cooldown_time,
		false
	);
}

void AEnemyCharacter::ResetAttack()
{
	bisAttacking = false;
}

void AEnemyCharacter::OnHitOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyCharacter* CharacterClass = Cast<AMyCharacter>(OtherActor))
	{
		if (CharacterClass->HP > attack_damage)
		{
			CharacterClass->Damage(attack_damage);

			UE_LOG(LogTemp, Warning, TEXT("%d"), CharacterClass->HP);
		}
		else if (CharacterClass->HP < attack_damage)
		{
			if (AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				SetActorLocation(ori_pos);

				GameMode->KillPlayer(CharacterClass);
			}
		}
	}
}