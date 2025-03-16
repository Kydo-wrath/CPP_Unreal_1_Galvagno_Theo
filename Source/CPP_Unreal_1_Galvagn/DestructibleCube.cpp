// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleCube.h"

// Sets default values
ADestructibleCube::ADestructibleCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
}

// Called when the game starts or when spawned
void ADestructibleCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleCube::DestroyObject_Implementation()
{
	Destroy();
}

