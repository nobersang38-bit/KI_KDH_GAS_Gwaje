// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_ActorSpawn.generated.h"

/**
 * 
 */
UCLASS()
class KI_KDH_GAS_GWAJE_API UGA_ActorSpawn : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AGASEffectActor> SpawnActorClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<TSubclassOf<UGameplayEffect>> ApplyEffectClasses;
};
