// Fill out your copyright notice in the Description page of Project Settings.


#include "BarWidget.h"

void UBarWidget::SetPosition(const FVector2D& position)
{
	Cast<UCanvasPanelSlot>(MProgressionBar->Slot)->SetPosition(position);
}

void UBarWidget::SetPercent(const float& Percent)
{
	float percentSetter = MProgressionBar->GetPercent() + Percent;
	MProgressionBar->SetPercent(percentSetter);

	ColorTest = MPercentBarColor->GetLinearColorValue(percentSetter);
	MProgressionBar->SetFillColorAndOpacity(ColorTest);
}

void UBarWidget::NativeConstruct()
{
	MProgressionBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progression")));

	if (MProgressionBar == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Description widget : Life not found"));
}
