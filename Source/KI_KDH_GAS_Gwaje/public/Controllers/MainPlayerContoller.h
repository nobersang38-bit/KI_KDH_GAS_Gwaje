// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Common/CommonDelegates.h"
#include "MainPlayerContoller.generated.h"
/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API AMainPlayerContoller : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCurrentAndMaxChanged OnChangeHealth;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCurrentAndMaxChanged OnChangeMana;
};
