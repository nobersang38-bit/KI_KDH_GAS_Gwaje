// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainHUD.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetInstance)
	{
		CreateWidget(GetOwningPlayerController(), MainWidgetInstance)->AddToViewport();
	}
}
