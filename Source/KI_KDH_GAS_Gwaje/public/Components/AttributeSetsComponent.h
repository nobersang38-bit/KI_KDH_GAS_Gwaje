// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "AttributeSetsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KI_KDH_GAS_GWAJE_API UAttributeSetsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeSetsComponent();

	UFUNCTION(BlueprintCallable)
	void AddAttributeSetsToASC(AActor* InOwnerActor);

	UFUNCTION(BlueprintCallable)
	bool FindAttributeSet(FGameplayTag InTag, TSubclassOf<UAttributeSet>& OutAttributeSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeSetSet")
	bool bAddAttributeSetsToASCOnStart = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeSetSet")
	TMap<FGameplayTag, TSubclassOf<UAttributeSet>> AttributeSets;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void AttributeEqualCheck();

	UPROPERTY(EditAnywhere, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bAttributeSetEqualCheck = false;

	UPROPERTY(VisibleAnywhere, Category = "Debug", meta = (AllowPrivateAccess = "true", DisplayName = "어트리뷰트셋 검사결과"))
	FText AttributeSetEqualCheckDescription;
};
