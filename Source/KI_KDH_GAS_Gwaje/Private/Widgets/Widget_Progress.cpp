// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_Progress.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Controllers/MainPlayerContoller.h"


void UWidget_Progress::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ProgressSize)
	{
		DefaultProgressSizeWidth = ProgressSize->GetWidthOverride();
	}
}

void UWidget_Progress::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	Name->SetText(BaseName);
	ProgressBar->SetFillColorAndOpacity(BaseProgressBarColor);
	ProgressSize->SetWidthOverride(BaseProgressWidth);
}

void UWidget_Progress::SetName(FText InName)
{
	if (Name)
	{
		Name->SetText(InName);
	}
}

void UWidget_Progress::SetName(FString InName)
{
	if (Name)
	{
		Name->SetText(FText::FromString(InName));
	}
}

void UWidget_Progress::UpdateValue(float CurrentValue, float MaxValue)
{
	if (!ProgressBar) return;
	if (!ValueText) return;

	float ResultValue = FMath::Clamp(CurrentValue / MaxValue, 0.0f, 1.0f);

	FText ResultText = FText::FromString(
		FString::Printf( TEXT("%.0f/%.0f"), CurrentValue, MaxValue ) 
	);

	ProgressBar->SetPercent(ResultValue);
	ValueText->SetText(ResultText);

	if (bFirstChangeValue)
	{
		bFirstChangeValue = false;
		DefaultMaxValue = MaxValue;
	}
	else
	{
		float ResulWidth = (MaxValue / DefaultMaxValue) * DefaultProgressSizeWidth;
		ProgressSize->SetWidthOverride(ResulWidth);
	}
}
