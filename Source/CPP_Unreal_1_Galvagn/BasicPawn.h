// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "BasicPawn.generated.h"

UCLASS()
class CPP_UNREAL_1_GALVAGN_API ABasicPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyControllerChanged() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetMappingContext(bool value);
	void ExitCube(const FInputActionValue& value);
	void MoveInputOn(const FInputActionValue& value);
	void MoveInputOff(const FInputActionValue& value);
	void MoveCubeDirection();
	void RotateCube();
	void SmoothMovement(const float& MoveAccelerationValue, const float& MovedecelerationValue, const float deltaTime);
	void SmoothRotation(const float& RotationAccelerationValue, const float& RotationdecelerationValue, const float deltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Movement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Exit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* CubeControlContext;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_CubeMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement settings", meta = (AllowPrivateAccess = "true"))
	float RotationMaxSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement settings", meta = (AllowPrivateAccess = "true"))
	float MovementMaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement settings", meta = (AllowPrivateAccess = "true"))
	float MovementAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement settings", meta = (AllowPrivateAccess = "true"))
	float MovementDeceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement settings", meta = (AllowPrivateAccess = "true"))
	float RotationAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement settings", meta = (AllowPrivateAccess = "true"))
	float RotationDeceleration;

	bool NegateMovement;
	bool NegateRotation;

	APawn* MpreviousPawn;

	float MCurrentRotationSpeed;
	float MCurrentMovementSpeed;

	FVector MMovementInput;

	float AccelerateMovement;
	float AccelerateRotation;

	float DecelerateMovement;
	float DevelerateRotation;

	FRotator RootRotation;
};
