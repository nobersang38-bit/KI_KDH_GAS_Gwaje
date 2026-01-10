// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GAS_Enemy.h"
#include "Components/GwajeAbilitySystemComponent.h"
#include "Components/AbilitiesComponent.h"
#include "AttributeSets/CommonAttributeSet.h"
#include "Components/EnemyAttributeSetComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/Widget_Progress.h"
#include "GameplayEffect.h"


// Sets default values
AGAS_Enemy::AGAS_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ASC = CreateDefaultSubobject<UGwajeAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitiesComponent = CreateDefaultSubobject<UAbilitiesComponent>(TEXT("AbilitiesComponent"));
	AttributeSet = CreateDefaultSubobject<UCommonAttributeSet>(TEXT("AttributeSet"));
	EnemyAttributeSetComponent = CreateDefaultSubobject<UEnemyAttributeSetComponent>(TEXT("EnemyAttributeSetComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGAS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	UWidget_Progress* HealthWidget = Cast<UWidget_Progress>(WidgetComponent->GetWidget());
	if (HealthWidget)
	{
		OnChangeHealth.AddUniqueDynamic(HealthWidget, &UWidget_Progress::UpdateValue);
	}

	GASInitialize();
}

// Called every frame
void AGAS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* AGAS_Enemy::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(ASC);
}

void AGAS_Enemy::GASInitialize()
{

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		if (InitializeEffect)
		{

			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(InitializeEffect, 1, EffectContext);
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}