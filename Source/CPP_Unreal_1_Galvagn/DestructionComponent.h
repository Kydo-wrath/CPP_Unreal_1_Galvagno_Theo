// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "Destructible.h"
#include "RPGHUD.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include "DestructionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_UNREAL_1_GALVAGN_API UDestructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestructionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	UFUNCTION(BlueprintCallable)
	void DestroyOtherActor();

	void DestructionBeam();

private:

	bool TryGetHUD();
	bool TryGetController();

	

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycast setting", meta = (AllowPrivateAccess = "true"))
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bar percent gain", meta = (AllowPrivateAccess = "true"))
	float Gain;

	AActor* MDestuctible;

	APlayerController* Controller;

	ARPGHUD* HUD;
};
