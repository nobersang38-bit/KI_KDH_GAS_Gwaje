// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentAndMaxChanged, float, CurrentValue, float, MaxValue);
/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UCommonDelegates : public UObject
{
	GENERATED_BODY()
};
