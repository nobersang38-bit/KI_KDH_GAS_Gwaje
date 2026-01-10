// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemyAttributeSetComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSets/CommonAttributeSet.h"
#include "Characters/GAS_Enemy.h"

UEnemyAttributeSetComponent::UEnemyAttributeSetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UEnemyAttributeSetComponent::BindAttributeDelegates()
{
	if (!Super::BindAttributeDelegates()) return false;

	if (AGAS_Enemy* Character = Cast<AGAS_Enemy>(GetOwner()))
	{
		Enemy = Character;
	}
	else return false;

	//최대체력
	FOnGameplayAttributeValueChange& OnMaxHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UCommonAttributeSet::GetMaxHealthAttribute());
	OnMaxHealthChange.AddUObject(this, &UEnemyAttributeSetComponent::UpdateMaxHealth);

	//체력
	FOnGameplayAttributeValueChange& OnHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UCommonAttributeSet::GetHealthAttribute());
	OnHealthChange.AddUObject(this, &UEnemyAttributeSetComponent::UpdateHealth);

	return true;
}

void UEnemyAttributeSetComponent::UpdateMaxHealth(const FOnAttributeChangeData& InData)
{
	if (Enemy.IsValid())
	{
		Enemy->OnChangeHealth.Broadcast(Enemy->GetEnemyAttributeSet()->GetHealth(), InData.NewValue);
	}
}

void UEnemyAttributeSetComponent::UpdateHealth(const FOnAttributeChangeData& InData)
{
	if (Enemy.IsValid())
	{
		Enemy->OnChangeHealth.Broadcast(InData.NewValue, Enemy->GetEnemyAttributeSet()->GetMaxHealth());
	}
}