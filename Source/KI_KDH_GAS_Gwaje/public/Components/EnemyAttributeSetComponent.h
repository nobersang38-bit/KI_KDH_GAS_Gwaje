// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AttributeSetComponent.h"
#include "GameplayEffectTypes.h"
#include "EnemyAttributeSetComponent.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UEnemyAttributeSetComponent : public UAttributeSetComponent
{
	GENERATED_BODY()
public:
	UEnemyAttributeSetComponent();

protected:
	virtual bool BindAttributeDelegates() override;

protected:
	void UpdateMaxHealth(const FOnAttributeChangeData& InData);
	void UpdateHealth(const FOnAttributeChangeData& InData);

private:
	TWeakObjectPtr<class AGAS_Enemy> Enemy = nullptr;
};

