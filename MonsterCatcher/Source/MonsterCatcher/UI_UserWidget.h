// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UI_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERCATCHER_API UUI_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HPBar;

    UFUNCTION(BlueprintCallable)
    void SetHPPercent(float Percent);
};
