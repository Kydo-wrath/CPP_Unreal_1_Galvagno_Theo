// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingCube.h"

// Sets default values
AMovingCube::AMovingCube()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	m_CubeMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		m_CubeMesh->SetStaticMesh(CubeVisualAsset.Object);
		m_CubeMesh->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Can't find it"));

	oscillation = 0;
	oscillationZ = 0;
	m_Speed = 10;
	m_Range = 100;
	moveInCircle = false;
	m_diameter = 100;
}

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingCube::MoveOscillate(const float& speedValue, const float& RangeValue, const float& deltaTime)
{ 
	oscillation += deltaTime;

	//Code line found with research to make the value oscillate and normalize it.

	float Frequency = (FMath::Sin(oscillation * speedValue) + 1) / 2;

	//Set the cube location between his base location and the range value on the X axis. 

	m_CubeMesh->SetRelativeLocation(FVector(FMath::Lerp( 0, RangeValue, Frequency), 0.0, 0.0));
}

void AMovingCube::Movecircle(const float& speedValue, const float& RangeValue, const float& deltaTime)
{
	oscillation += deltaTime;
	oscillationZ += deltaTime;

	//Code line found with research to make the value oscillate and normalize it.

	float FrequencyX = (FMath::Sin(oscillation * speedValue) + 1) / 2;

	//Code Adapeted for the Z axis, use Cos to get the circle movement

	float FrequencyZ = (FMath::Cos(oscillationZ * speedValue) + 1) / 2;

	//Set the cube location between his base location and the diameter value on the X axis and Z axis. 

	m_CubeMesh->SetRelativeLocation(FVector(FMath::Lerp(0, RangeValue, FrequencyX), FMath::Lerp(0, RangeValue, FrequencyZ), 0.0));
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!moveInCircle)
		MoveOscillate(m_Speed, m_Range, DeltaTime);
	else
		Movecircle(m_Speed, m_diameter,DeltaTime);
}

