// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingCube.generated.h"

UCLASS()
class CPP_UNREAL_1_GALVAGN_API AMovingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveOscillate(const float& speedValue, const float& RangeValue, const float& deltaTime);
	void Movecircle(const float& speedValue, const float& RangeValue, const float& deltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool moveInCircle;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_CubeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "oscillation", meta = (AllowPrivateAccess = "true"))
	float m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "oscillation", meta = (AllowPrivateAccess = "true"))
	float m_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "circle movement", meta = (AllowPrivateAccess = "true"))
	float m_diameter;

	float oscillation;
	float oscillationZ;
};
