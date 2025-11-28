// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ThrowKnifeActor.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
//WeaponComponent::WeaponComponent()
//{
//	// Default offset from the character location for projectiles to spawn
//	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
//}

//void WeaponComponent::Fire()
//{
//	// Try and fire a projectile
//	//if (ProjectileClass != nullptr)
//	//{
//	//	UWorld* const World = GetWorld();
//	//	if (World != nullptr)
//	//	{
//	//		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
//	//		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
//	//		// 	MuzzleOffset はカメラ空間にあるため、キャラクターの位置からオフセットする前にワールド空間に変換して最終的な銃口の位置を見つけます。
//	//		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
//
//	//		//	スポーン衝突処理オーバーライドを設定する
//	//		FActorSpawnParameters ActorSpawnParams;
//	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
//
//	//		// 銃口から発射物を生成する
//	//		World->SpawnActor<AThrowKnifeActor>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
//	//	}
//	//}
//}

//bool WeaponComponent::knife_pro()
//{
//	// Set up action bindings
//	//if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
//	//{
//	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//	//	{
//	//		// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
//	//		Subsystem->AddMappingContext(FireMappingContext, 1);
//	//	}
//
//	//	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
//	//	{
//	//		// Fire
//	//		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UMyProject4WeaponComponent::Fire);
//	//	}
//	//
//	//}
//
//	//return true;
//}

