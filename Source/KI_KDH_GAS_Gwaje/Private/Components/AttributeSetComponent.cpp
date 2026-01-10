// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeSetComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values for this component's properties
UAttributeSetComponent::UAttributeSetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UAttributeSetComponent::BeginPlay()
{
	Super::BeginPlay();
	ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	BindAttributeDelegates();
}

bool UAttributeSetComponent::BindAttributeDelegates()
{
	// 바인딩 하는 곳
	return ASC != nullptr;
}
