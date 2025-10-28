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
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// TPSカメラ
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	ThirdPersonCamera->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// FPSカメラ
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), TEXT("head")); // 頭のSocketにくっつける想定
	FirstPersonCamera->bUsePawnControlRotation = false;

	//グラップルケーブル
	GrappleCable = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleCable"));
	GrappleCable->SetupAttachment(FirstPersonCamera);
	GrappleCable->SetVisibility(false);

	isPers = true;
	isRunning = false;
	isGrappling = false;
	Distance = 0.f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	

	if (isPers)
	{
		FirstPersonCamera->SetActive(true);
		ThirdPersonCamera->SetActive(false);
	}
	else
	{
		FirstPersonCamera->SetActive(false);
		ThirdPersonCamera->SetActive(true);
	}
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

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsFiringGrapple)
	{
		float FireSpeed = 3000.f; // ケーブル発射速度
		CurrentCableLength += FireSpeed * DeltaTime;

		FVector CableEnd = GrappleStart + GrappleDir * CurrentCableLength;

		// ケーブル描画
		GrappleAnchor->SetWorldLocation(CableEnd);

		// 当たり判定
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(Hit, GrappleStart, CableEnd, ECC_Visibility, Params))
		{
			// 当たった瞬間、振り子状態に移行
			bIsFiringGrapple = false;
			isGrappling = true;

			GrabPoint = Hit.ImpactPoint;
			TargetCableLength = FVector::Distance(GetActorLocation(), GrabPoint);
			CurrentCableLength = TargetCableLength;

			GrappleAnchor->SetWorldLocation(GrabPoint);
			GrappleCable->SetAttachEndToComponent(GrappleAnchor, NAME_None);
		}
	}

	if (isGrappling)
	{
		FVector ActorLoc = GetActorLocation();
		FVector ToAnchor = GrabPoint - ActorLoc;
		FVector RopeDir = ToAnchor.GetSafeNormal();

		// -----------------------------
		// ① ロープを短くする処理
		// -----------------------------
		float MinRopeLength = 20.f;        // 短くできる最短距離
		float ShortenSpeed = 1000.f;         // 1秒あたり短くする速度

		float TargetLength = FMath::Clamp(CurrentCableLength - ShortenSpeed * DeltaTime, MinRopeLength, CurrentCableLength);
		CurrentCableLength = FMath::FInterpTo(CurrentCableLength, TargetLength, DeltaTime, 5.f);

		// -----------------------------
		// ② キャラクターに補正力をかける
		// -----------------------------
		FVector CorrectedPos = GrabPoint - RopeDir * CurrentCableLength;
		FVector Correction = CorrectedPos - ActorLoc;

		GetCharacterMovement()->AddForce(Correction * 500.f);

		// 重力
		GetCharacterMovement()->AddForce(FVector(0.f, 0.f, -980.f * GetCharacterMovement()->Mass));

		// ロープ方向速度除去
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
																														
		EnhancedInputConponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &AMyCharacter::ZoomIn);		//カメラズームイン
		EnhancedInputConponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &AMyCharacter::ZoomOut);		//カメラズームアウト
																														
		EnhancedInputConponent->BindAction(PersAction, ETriggerEvent::Started, this, &AMyCharacter::Pers);				//視点切り替え
																														
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

	if (Controller != nullptr && !isGrappling)
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

void AMyCharacter::ZoomIn(const FInputActionValue& Value)
{
	if (CameraBoom->TargetArmLength > 200)
	CameraBoom->TargetArmLength -= 30;
}

void AMyCharacter::ZoomOut(const FInputActionValue& Value)
{
	if (CameraBoom->TargetArmLength < 600)
	CameraBoom->TargetArmLength += 30;
}


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

void AMyCharacter::Run(const FInputActionValue& Value)
{
	isRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void AMyCharacter::StopRun(const FInputActionValue& Value)
{
	isRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMyCharacter::Grappling(const FInputActionValue& Value)
{
	if (isGrappling || bIsFiringGrapple) return;

	bIsFiringGrapple = true;

	// 発射開始位置と方向
	GrappleStart = FirstPersonCamera->GetComponentLocation();
	if (isPers)
	{
		GrappleDir = FirstPersonCamera->GetForwardVector();
	}
	else
	{
		GrappleDir = ThirdPersonCamera->GetForwardVector();
	}

	CurrentCableLength = 0.f;

	// ケーブル設定
	GrappleCable->SetVisibility(true);
	GrappleCable->bEnableStiffness = true;
	GrappleCable->bEnableCollision = false;
	GrappleCable->NumSegments = 10;
	GrappleCable->SolverIterations = 16;

	if (!GrappleAnchor)
	{
		GrappleAnchor = NewObject<USceneComponent>(this);
		GrappleAnchor->RegisterComponent();
	}

}

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
