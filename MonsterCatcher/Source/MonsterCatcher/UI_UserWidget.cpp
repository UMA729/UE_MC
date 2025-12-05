// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_UserWidget.h"


void UUI_UserWidget::SetHPPercent(float Percent)
{
    if (HPBar)
    {
        HPBar->SetPercent(Percent);
    }
}