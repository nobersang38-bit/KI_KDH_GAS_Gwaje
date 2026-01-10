// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_FireBall.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UGEEC_FireBall : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGEEC_FireBall();

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MultiplyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Multiply = 2.0f;
};
