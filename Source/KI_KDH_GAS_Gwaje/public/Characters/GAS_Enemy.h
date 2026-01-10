// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Common/CommonDelegates.h"
#include "GAS_Enemy.generated.h"

UCLASS()
class KI_KDH_GAS_GWAJE_API AGAS_Enemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGAS_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	inline class UCommonAttributeSet* GetEnemyAttributeSet() const { return AttributeSet; }

	UFUNCTION()
	void GASInitialize();

	FOnCurrentAndMaxChanged OnChangeHealth;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Component")
	TObjectPtr<class UGwajeAbilitySystemComponent> ASC = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Component")
	TObjectPtr<class UAbilitiesComponent> AbilitiesComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Component")
	TObjectPtr<class UEnemyAttributeSetComponent> EnemyAttributeSetComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UWidgetComponent> WidgetComponent = nullptr;

	UPROPERTY()
	TObjectPtr<class UCommonAttributeSet> AttributeSet = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> InitializeEffect = nullptr;

};
