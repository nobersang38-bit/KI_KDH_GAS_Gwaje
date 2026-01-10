// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UWidget_MainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWidget_PlayerProgressGroup> WBP_PlayerProgressGroup = nullptr;

private:
};
