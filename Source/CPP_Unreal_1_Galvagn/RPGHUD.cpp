// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHUD.h"

void ARPGHUD::SetlifeBarPosition(const FVector2D& position)
{
	MLifeBar->SetPosition(position);
}

void ARPGHUD::SetPercentInBar(const float& Percent)
{
	MLifeBar->SetPercent(Percent);
}

void ARPGHUD::BeginPlay()
{
	MLifeBar = Cast<UBarWidget>(CreateWidget(GetWorld(), MBarWidgetPrefab));
	MLifeBar->AddToViewport();
}
