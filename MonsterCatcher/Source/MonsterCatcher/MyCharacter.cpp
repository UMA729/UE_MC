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

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation

	// FPSカメラ
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), TEXT("head")); // 頭のSocketにくっつける想定
	FirstPersonCamera->bUsePawnControlRotation = true;

	isPers = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputConponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputConponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputConponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputConponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		EnhancedInputConponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		EnhancedInputConponent->BindAction(PersAction, ETriggerEvent::Triggered, this, &AMyCharacter::Pers);

		//EnhancedInputConponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyCharacter::Run);
		//EnhancedInputConponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
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
		AddControllerPitchInput(LookAxisVector.Y);
	}

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
//
//void AMyCharacter::Run(const FInputActionValue& Value)
//{
//
//}