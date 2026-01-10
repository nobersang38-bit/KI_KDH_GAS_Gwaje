// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "AttributeSetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KI_KDH_GAS_GWAJE_API UAttributeSetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeSetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual bool BindAttributeDelegates();
protected:

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> ASC = nullptr;
};
