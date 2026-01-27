// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

//入力関係
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

//リグ
#include "ControlRig.h"
#include "ControlRigComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	mCapsule->SetupAttachment(RootComponent);

	mSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SMesh"));
	mSMesh->SetupAttachment(mCapsule);


	mSpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	mSpringArm->SetupAttachment(mCapsule);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm);


	mControlRig = CreateDefaultSubobject<UControlRigComponent>("ControlRig");
	mControlRig->SetupAttachment(mSMesh);


}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(mIM_Key, 0);
		}
	}


	mControlRig->bUpdateRigOnTick = true;
	mControlRig->bUpdateInEditor = true;
	TArray<FControlRigComponentMappedElement> Map;
	if (mControlRig)
	{
		// 必要に応じてボーンのマッピングなどをここで追加
		TArray<FName> BoneNames;
		mSMesh->GetBoneNames(BoneNames);
		for (const FName& BoneName : BoneNames)
		{
			FControlRigComponentMappedElement element;
			element.ComponentReference.ComponentProperty = TEXT("SMesh");//動かすメッシュの接続
			element.TransformIndex = mSMesh->GetBoneIndex(BoneName);
			element.TransformName = BoneName;
			element.ElementType = ERigElementType::Bone;
			element.ElementName = BoneName;
			element.Direction = EControlRigComponentMapDirection::Output;
			Map.Add(element);
		}
		mControlRig->AddMappedElements(Map);
	}

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		EnhancedInputComponent->BindAction(mIA, ETriggerEvent::Triggered, this, &AMyPawn::KeySet);

	}
}

void AMyPawn::KeySet(const FInputActionValue& Value)
{
	// input is a Vector2D
	bool b = Value.Get<bool>();
	if (b == true)
	{
		ControlRig = mControlRig->GetControlRig();
		if (!mControlRig || !mControlRig->GetControlRig())
		{
			UE_LOG(LogTemp, Warning, TEXT("aaaa"));
			return;
		}

		FName name = TEXT("joint1_ctrl");
		URigHierarchy* Hierarchy = ControlRig->GetHierarchy();
		FRigElementKey ControlKey(name, ERigElementType::Control);
		if (!ControlRig->GetHierarchy()->Contains(ControlKey))
		{
			UE_LOG(LogTemp, Warning, TEXT("bbbb"));
			return;
		}

		key_count += 1.0f;
		FRotator Rot(0.f, 0.f, key_count);

		//リグを動かす型は<>で設定
		ControlRig->SetControlValue<FRotator>(name, Rot, false, FRigControlModifiedContext());
		//ControlRig->SetControlValue<FTransform>(name, NewTransform, false, FRigControlModifiedContext());
	}
}

