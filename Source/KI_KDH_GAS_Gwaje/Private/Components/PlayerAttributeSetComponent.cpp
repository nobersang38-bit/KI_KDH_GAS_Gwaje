// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerAttributeSetComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSets/CommonAttributeSet.h"
#include "GameFramework/Character.h"
#include "Controllers/MainPlayerContoller.h"
#include "KI_KDH_GAS_Gwaje/KI_KDH_GAS_GwajeCharacter.h"

UPlayerAttributeSetComponent::UPlayerAttributeSetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UPlayerAttributeSetComponent::BindAttributeDelegates()
{
	if (!Super::BindAttributeDelegates()) return false;

	if (AKI_KDH_GAS_GwajeCharacter* Character = Cast<AKI_KDH_GAS_GwajeCharacter>(GetOwner()))
	{
		Player = Character;
		if (!Player->GetController()) return false;

		Controller = Cast<AMainPlayerContoller>(Player->GetController());

		if (!Controller.IsValid()) return false;
	}
	else return false;
	//최대체력
	FOnGameplayAttributeValueChange& OnMaxHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UCommonAttributeSet::GetMaxHealthAttribute());
	OnMaxHealthChange.AddUObject(this, &UPlayerAttributeSetComponent::UpdateMaxHealth);

	//체력
	FOnGameplayAttributeValueChange& OnHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UCommonAttributeSet::GetHealthAttribute());
	OnHealthChange.AddUObject(this, &UPlayerAttributeSetComponent::UpdateHealth);

	//최대마나
	FOnGameplayAttributeValueChange& OnMaxManaChange = ASC->GetGameplayAttributeValueChangeDelegate(UCommonAttributeSet::GetMaxManaAttribute());
	OnMaxManaChange.AddUObject(this, &UPlayerAttributeSetComponent::UpdateMaxMana);

	//마나
	FOnGameplayAttributeValueChange& OnManaChange = ASC->GetGameplayAttributeValueChangeDelegate(UCommonAttributeSet::GetManaAttribute());
	OnManaChange.AddUObject(this, &UPlayerAttributeSetComponent::UpdateMana);

	return true;
}

void UPlayerAttributeSetComponent::UpdateMaxHealth(const FOnAttributeChangeData& InData)
{
	if (Controller.IsValid())
	{
		Controller->OnChangeHealth.Broadcast(Player->GetPlayerAttributeSet()->GetHealth(), InData.NewValue);
	}
}

void UPlayerAttributeSetComponent::UpdateHealth(const FOnAttributeChangeData& InData)
{
	if (Controller.IsValid())
	{
		Controller->OnChangeHealth.Broadcast(InData.NewValue, Player->GetPlayerAttributeSet()->GetMaxHealth());
	}
}

void UPlayerAttributeSetComponent::UpdateMaxMana(const FOnAttributeChangeData& InData)
{
	if (Controller.IsValid())
	{
		Controller->OnChangeMana.Broadcast(Player->GetPlayerAttributeSet()->GetMana(), InData.NewValue);
	}
}

void UPlayerAttributeSetComponent::UpdateMana(const FOnAttributeChangeData& InData)
{
	if (Controller.IsValid())
	{
		Controller->OnChangeMana.Broadcast(InData.NewValue, Player->GetPlayerAttributeSet()->GetMaxMana());
	}
}
