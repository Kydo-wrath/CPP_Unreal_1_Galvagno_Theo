// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Widget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"
#include <Components/CanvasPanelSlot.h>
#include "BarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPP_UNREAL_1_GALVAGN_API UBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetPosition(const FVector2D& position);
	void SetPercent(const float& Percent);	

protected:

	virtual void NativeConstruct() override;

private:

	UProgressBar* MProgressionBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Percent bar color setting", meta = (AllowPrivateAccess = "true"))
	UCurveLinearColor* MPercentBarColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Percent bar color setting", meta = (AllowPrivateAccess = "true"))
	FLinearColor ColorTest;


};
