// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GEEC/GEEC_FireBall.h"
#include "AttributeSets/CommonAttributeSet.h"

UGEEC_FireBall::UGEEC_FireBall()
{

}

void UGEEC_FireBall::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (TargetASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

		FAggregatorEvaluateParameters EvaluateParameters;
		EvaluateParameters.SourceTags = SourceTags;
		EvaluateParameters.TargetTags = TargetTags;

		float Internal_Damage = Damage;
		if (TargetTags && TargetTags->HasTag(MultiplyTag))
		{
			Internal_Damage *= Multiply;
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					UCommonAttributeSet::GetHealthAttribute(),
					EGameplayModOp::Additive,
					-Internal_Damage
				)
			);
		}
	}
}
