// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilitiesComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/GwajeAbilitySystemComponent.h"

// Sets default values for this component's properties
UAbilitiesComponent::UAbilitiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
		if (bGiveAbilitiesToASCOnStart)
		{
			GiveAbilitiesToASC(GetOwner());
		}
	}


	// ...
	
}

void UAbilitiesComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	AbilityIDEqualCheck();
}


// Called every frame
void UAbilitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilitiesComponent::AbilityIDEqualCheck()
{
	if (bAbilityIDEqualCheck)
	{
		bAbilityIDEqualCheck = false;

		TArray<FAbilitySet> TempAbilitySetArray;
		TArray<FGameplayTag> TempGameplayTagArray;

		Abilities.GenerateValueArray(TempAbilitySetArray);
		Abilities.GenerateKeyArray(TempGameplayTagArray);

		FString ResultDescription;

		for (int i = 0; i < TempAbilitySetArray.Num(); i++)
		{
			if (TempAbilitySetArray[i].Ability == nullptr)
			{
				ResultDescription = FString::Printf(TEXT("%d번 IDX의 어빌리티가 설정되지 않았습니다"), i);
				AbilityIDEqualCheckDescription = FText::FromString(ResultDescription);
				return;
			}

			for (int j = 0; j < TempAbilitySetArray.Num(); j++)
			{
				if (i == j) continue;

				if (TempAbilitySetArray[i].AbilityID == TempAbilitySetArray[j].AbilityID)
				{
					ResultDescription = FString::Printf(TEXT("%d번 IDX와 %d번 IDX의 ID인 %d가 겹칩니다"), i, j, TempAbilitySetArray[i].AbilityID);
					AbilityIDEqualCheckDescription = FText::FromString(ResultDescription);
					return;
				}
			}
		}

		for (int i = 0; i < TempGameplayTagArray.Num(); i++)
		{
			if (TempGameplayTagArray[i].GetTagName() == FName())
			{
				ResultDescription = FString::Printf(TEXT("%d번 IDX의 태그가 설정되지 않았습니다"), i);
				AbilityIDEqualCheckDescription = FText::FromString(ResultDescription);
				return;
			}
		}

		ResultDescription = FString::Printf(TEXT("문제가 발견되지 않았습니다"));
		AbilityIDEqualCheckDescription = FText::FromString(ResultDescription);
		return;
	}
}

void UAbilitiesComponent::GiveAbilitiesToASC(AActor* InOwnerActor, int32 InLevel)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwnerActor);
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("UAbilitiesComponent::GiveAbilitiesToASC 오너에 AbilitySystemComponent가 없음!!"));
		return;
	}

	for (const auto& Ability : Abilities)
	{
		//FGameplayAbilitySpec(TSubclassOf<UGameplayAbility> InAbilityClass, int32 InLevel = 1, int32 InInputID = INDEX_NONE, UObject* InSourceObject = nullptr);
		FGameplayAbilitySpecHandle TempSpecHandle = ASC->GiveAbility(FGameplayAbilitySpec(
			Ability.Value.Ability, 
			InLevel, 
			Ability.Value.AbilityID, 
			InOwnerActor
		));

		AbilitySpecHandles.Add(Ability.Key, TempSpecHandle);
	}
}

bool UAbilitiesComponent::FindAbilitySet(FGameplayTag InTag, FAbilitySet& OutAbilitySet)
{
	if (!Abilities.Contains(InTag)) return false;

	OutAbilitySet = *Abilities.Find(InTag);
	return true;
}

void UAbilitiesComponent::ActivateAbilityByTag(FGameplayTag InTag)
{
	if (InTag.GetTagName() == FName()) return;

	if (!OwnerASC.IsValid())
	{
		OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
		if (!OwnerASC.IsValid()) return;
	}

	if (AbilitySpecHandles.Contains(InTag))
	{
		FGameplayAbilitySpecHandle* TempSpecHandle = AbilitySpecHandles.Find(InTag);
		if (TempSpecHandle && TempSpecHandle->IsValid() && OwnerASC.IsValid())
		{
			OwnerASC.Get()->TryActivateAbility(*TempSpecHandle);
		}
	}
}
