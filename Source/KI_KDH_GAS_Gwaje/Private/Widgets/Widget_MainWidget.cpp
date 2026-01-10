// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_MainWidget.h"
#include "Controllers/MainPlayerContoller.h"
#include "Widgets/Widget_PlayerProgressGroup.h"
#include "Widgets/Widget_Progress.h"

void UWidget_MainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AMainPlayerContoller* PC = Cast<AMainPlayerContoller>(GetOwningPlayer()))
	{

		if (WBP_PlayerProgressGroup)
		{
			if (UWidget_Progress* HPWidget = WBP_PlayerProgressGroup->GetProgress_HPWidget())
			{
				PC->OnChangeHealth.AddUniqueDynamic(HPWidget, &UWidget_Progress::UpdateValue);
			}

			if (UWidget_Progress* MPWidget = WBP_PlayerProgressGroup->GetProgress_MPWidget())
			{
				PC->OnChangeMana.AddUniqueDynamic(MPWidget, &UWidget_Progress::UpdateValue);
			}
		}
	}
}
