// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainWidgetInstance = nullptr;
};
