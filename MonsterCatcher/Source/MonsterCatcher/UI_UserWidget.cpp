// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_UserWidget.h"
#include "MyGameInstance.h"

void UUI_UserWidget::SetHPPercent(float Percent)
{
    if (HPBar)
    {
        UE_LOG(LogTemp, Warning, TEXT("%f"),Percent);
        HPBar->SetPercent(Percent);
    }
}

void UUI_UserWidget::SetKeyCount(int32 key_count)
{
    if (KeyCount)
    {
        KeyCount->SetText(FText::FromString(FString::Printf(TEXT("x%d"),key_count)));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("not text box"));
    }
}
