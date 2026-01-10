// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AttributeSetComponent.h"
#include "GameplayEffectTypes.h"
#include "PlayerAttributeSetComponent.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UPlayerAttributeSetComponent : public UAttributeSetComponent
{
	GENERATED_BODY()
public:
	UPlayerAttributeSetComponent();

protected:
	virtual bool BindAttributeDelegates() override;

protected:
	void UpdateMaxHealth(const FOnAttributeChangeData& InData);
	void UpdateHealth(const FOnAttributeChangeData& InData);
	void UpdateMaxMana(const FOnAttributeChangeData& InData);
	void UpdateMana(const FOnAttributeChangeData& InData);

private:
	TWeakObjectPtr<class AMainPlayerContoller> Controller = nullptr;
	TWeakObjectPtr<class AKI_KDH_GAS_GwajeCharacter> Player = nullptr;
};
