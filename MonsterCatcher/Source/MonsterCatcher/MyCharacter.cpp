// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "CableComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// カメラアームを作る (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// TPSカメラ
	//ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	//ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//ThirdPersonCamera->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// FPSカメラ
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(CameraBoom); // 頭のSocketにくっつける想定

	//グラップルケーブル
	GrappleCable = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleCable"));
	GrappleCable->SetVisibility(false);

	//GrappleCable->bEnableStiffness = true;	//張力を有効
	GrappleCable->bEnableCollision = false;		//衝突判定を切る
	GrappleCable->NumSegments = 10;
	GrappleCable->SolverIterations = 16;

	//isPers = true;
	isRunning = false;
	isGrappling = false;
	Distance = 0.f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();	

	GrappleCable->SetupAttachment(GetMesh(), FName("RightHand"));

	/*if (isPers)
	{
		if (FirstPersonCamera && ThirdPersonCamera)
		{
			FirstPersonCamera->SetActive(true);
			ThirdPersonCamera->SetActive(false);
		}
	}
	else
	{
		if (FirstPersonCamera && ThirdPersonCamera)
		{
			FirstPersonCamera->SetActive(false);
			ThirdPersonCamera->SetActive(true);
		}
	}*/
}

void AMyCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//毎フレーム更新
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ケーブル飛翔中（伸ばし中）
	if (bIsFiringGrapple && GrappleAnchor)
	{
		//ケーブルの位置を更新
		GrappleCable->SetWorldLocation(GrappleStart);

		float FireSpeed = 4000.f; // ケーブル伸びる速度
		CurrentCableLength = FMath::Min(CurrentCableLength + FireSpeed * DeltaTime, TargetCableLength);//線形補間

		//線形補間を元にケーブルを伸ばす
		FVector CableEnd = GrappleStart + GrappleDir * CurrentCableLength;
		//接着地点
		GrappleAnchor->SetWorldLocation(CableEnd);

		// 目標長さに達したら固定（命中済みなのでここで切り替え）
		if (CurrentCableLength >= TargetCableLength)
		{
			bIsFiringGrapple = false;
			isGrappling = true;
		}
	}

	// 振り子物理処理
	if (isGrappling)
	{
		FVector ActorLoc = GetActorLocation();
		FVector ToAnchor = GrabPoint - ActorLoc;
		FVector RopeDir = ToAnchor.GetSafeNormal();

		FVector CorrectedPos = GrabPoint - RopeDir * CurrentCableLength;
		FVector Correction = CorrectedPos - ActorLoc;

		GetCharacterMovement()->AddForce(Correction * 800.f);
		GetCharacterMovement()->AddForce(FVector(0, 0, -980.f * GetCharacterMovement()->Mass));

		FVector Velocity = GetCharacterMovement()->Velocity;
		float SpeedAlongRope = FVector::DotProduct(Velocity, RopeDir);
		FVector TangentialVelocity = Velocity - RopeDir * SpeedAlongRope;
		GetCharacterMovement()->Velocity = TangentialVelocity;
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputConponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputConponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);				//ジャンプ
		EnhancedInputConponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);		//ジャンプ停止
																														
		EnhancedInputConponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);			//移動
																														
		EnhancedInputConponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);			//視点移動
																														
		//EnhancedInputConponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &AMyCharacter::ZoomIn);		//カメラズームイン
		//EnhancedInputConponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &AMyCharacter::ZoomOut);		//カメラズームアウト
																														
		//EnhancedInputConponent->BindAction(PersAction, ETriggerEvent::Started, this, &AMyCharacter::Pers);				//視点切り替え
																														
		EnhancedInputConponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyCharacter::Run);				//ダッシュ
		EnhancedInputConponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);

		EnhancedInputConponent->BindAction(GrappleAction, ETriggerEvent::Triggered, this, &AMyCharacter::Grappling);			//ダッシュ停止
		EnhancedInputConponent->BindAction(GrappleAction, ETriggerEvent::Completed, this, &AMyCharacter::StopGrapple);			//ダッシュ停止
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && GetCharacterMovement()->IsFalling() == false || bIsFiringGrapple == false && isGrappling == false)
	{
		//キャラ正面を取得
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 正面へのベクトルを取得
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// 横方向のベクトルを取得 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 動きに反映
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	// 2軸のベクトルを取得
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//マウスの動きにあわせて視点に反映
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}

}

//ズームイン
void AMyCharacter::ZoomIn(const FInputActionValue& Value)
{
	if (CameraBoom->TargetArmLength > 200)
	CameraBoom->TargetArmLength -= 30;
}

//ズームアウト
void AMyCharacter::ZoomOut(const FInputActionValue& Value)
{
	if (CameraBoom->TargetArmLength < 600)
	CameraBoom->TargetArmLength += 30;
}

//視点切り替え
void AMyCharacter::Pers(const FInputActionValue& Value)
{
	isPers = !isPers;

	if (isPers)
	{
		ThirdPersonCamera->SetActive(false);
		FirstPersonCamera->SetActive(true);
	}
	else
	{
		ThirdPersonCamera->SetActive(true);
		FirstPersonCamera->SetActive(false);
	}
}

//ダッシュ
void AMyCharacter::Run(const FInputActionValue& Value)
{
	isRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

//ダッシュ停止
void AMyCharacter::StopRun(const FInputActionValue& Value)
{
	isRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

//グラップル
void AMyCharacter::Grappling(const FInputActionValue& Value)
{
	if (isGrappling || bIsFiringGrapple) return;

	GrappleCable->SetVisibility(true);
	bIsFiringGrapple = true;

	// ケーブル発射の開始位置（キャラの頭のソケット）
	GrappleStart = GetMesh()->GetSocketLocation(TEXT("RightHand"));
	GrappleDir = FirstPersonCamera->GetForwardVector();

	// 1回だけRayを飛ばす（ヒット判定）
	float TraceDistance = 3000.f;
	FVector TraceEnd = GrappleStart + GrappleDir * TraceDistance;

	FHitResult Hit;					//Rayのヒット結果
	FCollisionQueryParams Params;	//コリジョン判定を受け取る
	Params.AddIgnoredActor(this);	//

	//オブジェクトを探すレイ
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, GrappleStart, TraceEnd, ECC_Visibility, Params);

	//レイのデバッグ
	DrawDebugLine(GetWorld(), GrappleStart, TraceEnd, FColor::Green, false, 3.0f, 0, 2.0f);

	//レイがヒットすると入る
	if (bHit)
	{
		// Anchor（ケーブルの終端）を作成して命中位置に固定
		if (!GrappleAnchor)
		{
			GrappleAnchor = NewObject<USceneComponent>(this);
			GrappleAnchor->RegisterComponent();
		}
		//グラップルワイヤーの終点を接着地点へ
		GrappleCable->SetAttachEndToComponent(GrappleAnchor, NAME_None);

		//接着地点の座標を取得
		GrabPoint = Hit.ImpactPoint;

		// ケーブルを段階的に伸ばす準備
		CurrentCableLength = 0.f;
		TargetCableLength = FVector::Distance(GrappleStart, GrabPoint);
	}
	else
	{
		// 命中しなければ発射中断
		GrappleCable->SetVisibility(false);
		bIsFiringGrapple = false;
	}
}

//グラップル停止
void AMyCharacter::StopGrapple(const FInputActionValue& Value)
{
	if (!isGrappling && !bIsFiringGrapple) return;

	isGrappling = false;
	bIsFiringGrapple = false;

	GrappleCable->SetVisibility(false);

	if (GrappleAnchor)
	{
		GrappleAnchor->DestroyComponent();
		GrappleAnchor = nullptr;
	}

	// 通常の移動に戻す
	GetCharacterMovement()->SetMovementMode(MOVE_Falling);
}
