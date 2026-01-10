// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Progress.generated.h"

class UTextBlock;
class USizeBox;
class UProgressBar;

UCLASS()
class KI_KDH_GAS_GWAJE_API UWidget_Progress : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Name = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USizeBox> ProgressSize = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void SetName(FText InName);
	void SetName(FString InName);

	UFUNCTION(BlueprintCallable)
	void UpdateValue(float CurrentValue, float MaxValue);

protected:
	virtual void NativeOnInitialized() override;
	virtual void SynchronizeProperties() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set|Base")
	FText BaseName = FText::FromString(TEXT("이름을 정하세요"));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set|Base")
	FLinearColor BaseProgressBarColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set|Base")
	float BaseProgressWidth = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set|Runtime", meta = (ToolTip = "프로그래스바의 최대 넓이 배수"))
	float ProgressSizeMaxMultiply = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set|Runtime", meta = (ToolTip = "최대 넓이가 1커지면 ProgressSize는 몇배로 커질것인가"))
	float ProgressSizeMultiply = 2.0f;

private:
	UPROPERTY()
	float DefaultProgressSizeWidth = 0.0f;

	UPROPERTY()
	float DefaultMaxValue = 0.0f;

	UPROPERTY()
	bool bFirstChangeValue = true;
};
