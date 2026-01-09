// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeSetsComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values for this component's properties
UAttributeSetsComponent::UAttributeSetsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAttributeSetsComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bAddAttributeSetsToASCOnStart && GetOwner()) // 오너한테 해당 어트리뷰트 설정하기
	{
		AddAttributeSetsToASC(GetOwner());
	}
	// ...
	
}

void UAttributeSetsComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	AttributeEqualCheck();
}


// Called every frame
void UAttributeSetsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttributeSetsComponent::AttributeEqualCheck()
{
	if (bAttributeSetEqualCheck)
	{
		bAttributeSetEqualCheck = false;

		TArray<TSubclassOf<UAttributeSet>> TempAttributeSetsArray;
		TArray<FGameplayTag> TempGameplayTagArray;

		AttributeSets.GenerateValueArray(TempAttributeSetsArray);
		AttributeSets.GenerateKeyArray(TempGameplayTagArray);

		FString ResultDescription;

		for (int i = 0; i < TempAttributeSetsArray.Num(); i++)
		{
			if (TempAttributeSetsArray[i] == nullptr)
			{
				ResultDescription = FString::Printf(TEXT("%d번 IDX의 어빌리티가 설정되지 않았습니다"), i);
				AttributeSetEqualCheckDescription = FText::FromString(ResultDescription);
				return;
			}

			for (int j = 0; j < TempAttributeSetsArray.Num(); j++)
			{
				if (i == j) continue;

				if (TempAttributeSetsArray[i] == TempAttributeSetsArray[j])
				{
					ResultDescription = FString::Printf(TEXT("%d번 IDX와 %d번 IDX의 어트리뷰트셋이 겹칩니다"), i, j);
					AttributeSetEqualCheckDescription = FText::FromString(ResultDescription);
					return;
				}
			}
		}

		for (int i = 0; i < TempGameplayTagArray.Num(); i++)
		{
			if (TempGameplayTagArray[i].GetTagName() == FName())
			{
				ResultDescription = FString::Printf(TEXT("%d번 IDX의 태그가 설정되지 않았습니다"), i);
				AttributeSetEqualCheckDescription = FText::FromString(ResultDescription);
				return;
			}
		}

		ResultDescription = FString::Printf(TEXT("문제가 발견되지 않았습니다"));
		AttributeSetEqualCheckDescription = FText::FromString(ResultDescription);
		return;
	}
}

void UAttributeSetsComponent::AddAttributeSetsToASC(AActor* InOwnerActor)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwnerActor);
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("UAttributeSetsComponent::AddAttributeSetsToASC 오너에 AbilitySystemComponent가 없음!!"));
		return;
	}

	for (const auto& AttributeSet : AttributeSets)
	{
		UAttributeSet* NewSet = NewObject<UAttributeSet>(InOwnerActor, AttributeSet.Value);
		ASC->AddAttributeSetSubobject(NewSet);
	}
}

bool UAttributeSetsComponent::FindAttributeSet(FGameplayTag InTag, TSubclassOf<UAttributeSet>& OutAttributeSet)
{
	if (!AttributeSets.Contains(InTag)) return false;

	OutAttributeSet = *AttributeSets.Find(InTag);
	return true;
}
