// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "GASEffectActor.generated.h"

UCLASS()
class KI_KDH_GAS_GWAJE_API AGASEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGASEffectActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetDamageEffectSpecHandle(const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandle);

	UFUNCTION()
	void OverlapActorsEmpty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void InitializeTriggerComponents();

	UFUNCTION()
	void OverlapEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set")
	bool IsSuccessDestroy = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set")
	float LifeTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set", meta = (ToolTip = "오버랩으로 사용할 콜리전의 태그의 이름은 어떤건가"))
	FName EffectTriggerTagName;

	UPROPERTY()
	TArray<TObjectPtr<class UShapeComponent>> EffectTriggerComponents;
	
	TArray<FGameplayEffectSpecHandle> DamageEffectSpecHandles;

private:	
	TSet<TWeakObjectPtr<AActor>> OverlapActors;
};
