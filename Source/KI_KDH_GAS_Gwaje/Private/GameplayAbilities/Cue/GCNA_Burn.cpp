// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/Cue/GCNA_Burn.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AGCNA_Burn::AGCNA_Burn()
{
	bAutoDestroyOnRemove = true;
}

bool AGCNA_Burn::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnVFX.IsValid())
	{
		SpawnVFX->Deactivate();
		SpawnVFX = nullptr;
	}

	if (MyTarget && VFX && Parameters.EffectContext.IsValid() && Parameters.EffectContext.GetHitResult())
	{
		SpawnVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(VFX, MyTarget->GetRootComponent(), FName(), Parameters.EffectContext.GetHitResult()->ImpactPoint, FRotator::ZeroRotator, EAttachLocation::KeepWorldPosition, false);
		
		return true;
	}
	return false;
}

bool AGCNA_Burn::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnVFX.IsValid())
	{
		SpawnVFX->Deactivate();
		SpawnVFX = nullptr;
	}
	return true;
}
