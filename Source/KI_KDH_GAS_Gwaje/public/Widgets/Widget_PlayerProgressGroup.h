// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PlayerProgressGroup.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UWidget_PlayerProgressGroup : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWidget_Progress> WBP_Progress_HP = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWidget_Progress> WBP_Progress_MP = nullptr;

public:
	inline UWidget_Progress* GetProgress_HPWidget() const { return WBP_Progress_HP; }
	inline UWidget_Progress* GetProgress_MPWidget() const { return WBP_Progress_MP; }
};
