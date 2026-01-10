// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GASEffectActor.h"
#include "Components/ShapeComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AGASEffectActor::AGASEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGASEffectActor::BeginPlay()
{
	Super::BeginPlay();
	InitializeTriggerComponents();
	SetLifeSpan(LifeTime);
}

void AGASEffectActor::InitializeTriggerComponents()
{
	TArray<UActorComponent*> TempShapeComponents = GetComponentsByTag(UShapeComponent::StaticClass(), EffectTriggerTagName);

	for (int i = 0; i < TempShapeComponents.Num(); i++)
	{
		if (UShapeComponent* ShapeComp = Cast<UShapeComponent>(TempShapeComponents[i]))
		{
			EffectTriggerComponents.Add(ShapeComp);
			ShapeComp->OnComponentBeginOverlap.AddDynamic(this, &AGASEffectActor::OverlapEffect);
		}
	}
}

void AGASEffectActor::OverlapEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this == OtherActor) return;
	if (OverlapActors.Contains(OtherActor)) return;
	if (GetOwner() && GetOwner() == OtherActor) return;

	if (!OtherComp->GetOwner())
	{
		Destroy();
	}
	
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldDynamic ||
		OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic
		)
	{
		Destroy();
	}

	FHitResult HitResult;
	FVector StartLocation = OverlappedComponent->GetComponentLocation();
	FVector EndLocation = OverlappedComponent->GetComponentLocation() + ((OtherComp->GetComponentLocation() - OverlappedComponent->GetComponentLocation()).GetSafeNormal() * 10000.0f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(50.0f), QueryParams);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.0f);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (ASC && !DamageEffectSpecHandles.IsEmpty())
	{
		for (const auto SpecHandle : DamageEffectSpecHandles)
		{
			if (!SpecHandle.IsValid()) continue;

			FGameplayEffectSpec* NewSpec = new FGameplayEffectSpec(*SpecHandle.Data.Get());
			FGameplayEffectSpecHandle NewHandle = FGameplayEffectSpecHandle(NewSpec);

			FGameplayEffectContextHandle ContextHandle = NewHandle.Data->GetContext();

			FGameplayEffectContextHandle NewContext = ASC->MakeEffectContext();
			NewContext.AddHitResult(HitResult);
			NewHandle.Data->SetContext(NewContext);

			ASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
		OverlapActors.Add(OtherActor);

		if (IsSuccessDestroy)
		{
			Destroy();
		}
	}
}

// Called every frame
void AGASEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGASEffectActor::SetDamageEffectSpecHandle(const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandle)
{
	DamageEffectSpecHandles = InGameplayEffectSpecHandle;
}

void AGASEffectActor::OverlapActorsEmpty()
{
	OverlapActors.Empty();
}

