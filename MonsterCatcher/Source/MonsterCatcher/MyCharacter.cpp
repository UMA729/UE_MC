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

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// �J�����A�[������� (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	ThirdPersonCamera->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// FPS�J����
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), TEXT("head")); // ����Socket�ɂ�������z��
	FirstPersonCamera->bUsePawnControlRotation = false;

	isPers = false;
	isRunning = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputConponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputConponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);				//�W�����v
		EnhancedInputConponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);		//�W�����v��~
																														
		EnhancedInputConponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);			//�ړ�
																														
		EnhancedInputConponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);			//���_�ړ�
																														
		EnhancedInputConponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &AMyCharacter::ZoomIn);		//�J�����Y�[���C��
		EnhancedInputConponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &AMyCharacter::ZoomOut);		//�J�����Y�[���A�E�g
																														
		EnhancedInputConponent->BindAction(PersAction, ETriggerEvent::Started, this, &AMyCharacter::Pers);				//���_�؂�ւ�
																														
		EnhancedInputConponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyCharacter::Run);				//�_�b�V��
		EnhancedInputConponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);			//�_�b�V����~
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//�L�������ʂ��擾
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// ���ʂւ̃x�N�g�����擾
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// �������̃x�N�g�����擾 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// �����ɔ��f
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	// 2���̃x�N�g�����擾
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//�}�E�X�̓����ɂ��킹�Ď��_�ɔ��f
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