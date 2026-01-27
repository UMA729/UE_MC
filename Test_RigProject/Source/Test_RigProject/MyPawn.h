// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UCapsuleComponent;
class UControlRigComponent;
class UControlRig;

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TEST_RIGPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(Category = "C_CODE", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent>  mCapsule;	//カプセルコンポーネント

	UPROPERTY(Category = "C_CODE", VisibleAnywhere)
	TObjectPtr <USkeletalMeshComponent> mSMesh;//スケルタルメッシュコンポーネント


	UPROPERTY(Category = "C_CODE", VisibleAnywhere)
	TObjectPtr<USpringArmComponent> mSpringArm;//スプリングアームコンポーネント

	UPROPERTY(Category = "C_CODE", VisibleAnywhere)
	TObjectPtr<UCameraComponent> mCamera;		//カメラコンポーネント


	UPROPERTY(Category = "C_CODE", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UControlRigComponent> mControlRig;

	UPROPERTY(EditAnywhere, Category = "Rig")
	UControlRig* ControlRig;


	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> mIM_Key;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> mIA;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void KeySet(const FInputActionValue& Value);

	float key_count{ 0 };
};
