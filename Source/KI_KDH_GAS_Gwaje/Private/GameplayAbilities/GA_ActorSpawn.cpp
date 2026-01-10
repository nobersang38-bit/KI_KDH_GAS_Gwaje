// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GA_ActorSpawn.h"
#include "Actors/GASEffectActor.h"
#include "AbilitySystemComponent.h"

void UGA_ActorSpawn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!SpawnActorClass || ApplyEffectClasses.IsEmpty())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!ActorInfo->AvatarActor.IsValid())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	EffectContext.AddInstigator(ActorInfo->AvatarActor.Get(), ActorInfo->AvatarActor.Get());

	TArray<FGameplayEffectSpecHandle> SpecHandles;

	for (const auto& EffectClass : ApplyEffectClasses)
	{
		if (!EffectClass) continue;

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
			EffectClass,
			GetAbilityLevel(),
			EffectContext
		);

		SpecHandles.Add(SpecHandle);
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ActorInfo->AvatarActor->GetActorLocation());
	SpawnTransform.SetRotation(ActorInfo->AvatarActor->GetActorForwardVector().ToOrientationQuat());
	AGASEffectActor* TempSpawnActor = GetWorld()->SpawnActorDeferred<AGASEffectActor>(SpawnActorClass, SpawnTransform);

	if (TempSpawnActor)
	{
		TempSpawnActor->SetOwner(ActorInfo->AvatarActor.Get());
		TempSpawnActor->SetDamageEffectSpecHandle(SpecHandles);
		TempSpawnActor->FinishSpawning(SpawnTransform);

		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}
