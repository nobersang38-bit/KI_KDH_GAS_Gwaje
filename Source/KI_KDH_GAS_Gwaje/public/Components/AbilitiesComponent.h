// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "AbilitiesComponent.generated.h"

USTRUCT(BlueprintType)
struct FAbilitySet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySet")
	int32 AbilityID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySet")
	TSubclassOf<class UGameplayAbility> Ability = nullptr;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KI_KDH_GAS_GWAJE_API UAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilitiesComponent();

	UFUNCTION(BlueprintCallable)
	void GiveAbilitiesToASC(AActor* InOwnerActor, int32 InLevel = 1);

	UFUNCTION(BlueprintCallable)
	bool FindAbilitySet(FGameplayTag InTag, FAbilitySet& OutAbilitySet);

	//현재 컴포넌트에서 추가한 태그를 사용하여 Ability를 실행
	UFUNCTION(BlueprintCallable)
	void ActivateAbilityByTag(FGameplayTag InTag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitiesSet")
	bool bGiveAbilitiesToASCOnStart = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitiesSet")
	TMap<FGameplayTag, FAbilitySet> Abilities;

	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandles;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void AbilityIDEqualCheck();

	UPROPERTY(EditAnywhere, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bAbilityIDEqualCheck = false;

	UPROPERTY(VisibleAnywhere, Category = "Debug", meta = (AllowPrivateAccess = "true", DisplayName = "어빌리티 아이디 검사결과"))
	FText AbilityIDEqualCheckDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UAbilitySystemComponent> OwnerASC = nullptr;
};
