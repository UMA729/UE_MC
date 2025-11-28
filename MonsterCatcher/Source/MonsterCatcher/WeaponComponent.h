// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AThrowKnifeActor;
/**
 * 
 */
class MONSTERCATCHER_API WeaponComponent
{
public:
	WeaponComponent();
	//ナイフのクラス
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AThrowKnifeActor> ProjectileClass;
	//発射位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool knife_pro();

	//発射
	void Fire();

	//ナイフのクラス変数
	AThrowKnifeActor* Character;
};
