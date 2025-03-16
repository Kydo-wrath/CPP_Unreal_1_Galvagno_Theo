// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BarWidget.h"
#include "RPGHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPP_UNREAL_1_GALVAGN_API ARPGHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void SetlifeBarPosition(const FVector2D& position);
	void SetPercentInBar(const float& Percent);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBarWidget> MBarWidgetPrefab;

	UBarWidget* MLifeBar;
};
