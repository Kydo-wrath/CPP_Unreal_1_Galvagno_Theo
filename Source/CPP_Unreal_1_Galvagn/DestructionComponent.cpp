// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructionComponent.h"

// Sets default values for this component's properties
UDestructionComponent::UDestructionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Range = 0.0;
	Gain = 0.0;
	m_Camera = nullptr;
	MDestuctible = nullptr;
}


// Called when the game starts
void UDestructionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UDestructionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DestructionBeam();
}

void UDestructionComponent::DestroyOtherActor()
{
	if (MDestuctible == nullptr)
	{
		return;
	}
	if (HUD != nullptr || TryGetHUD())
	{
		HUD->SetPercentInBar(Gain);

	}
	else
		UE_LOG(LogTemp, Error, TEXT("Description widget : Hud not found"));


	IDestructible::Execute_DestroyObject(MDestuctible);
}

void UDestructionComponent::DestructionBeam()
{
	
	FHitResult hit;

	ECollisionChannel channel(ECC_GameTraceChannel1);
	const FCollisionQueryParams traceParam(FName(TEXT("")),false, GetOwner());

	FVector startPosition = m_Camera->GetComponentLocation();
	FVector EndPosition = startPosition + m_Camera->GetForwardVector() * Range;
	
	if (!GetWorld()->LineTraceSingleByChannel(OUT hit, startPosition, EndPosition, channel, traceParam))
	{
		MDestuctible = nullptr;
		return;
	}

	AActor* hitActor = hit.GetActor();

	if (hitActor == nullptr)
	{
		MDestuctible = nullptr;
		return;
	}

	if (hitActor->GetClass()->ImplementsInterface(UDestructible::StaticClass()))
	{

		MDestuctible = hitActor;
	}
	else
	{
		MDestuctible = nullptr;
	}
}

bool UDestructionComponent::TryGetHUD()
{
	UWorld* world = GetWorld();

	if (world == nullptr)
		return false;

	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr)
		return false;

	HUD = Cast<ARPGHUD>(controller->GetHUD());
	if (HUD == nullptr)
		return false;

	return true;
}

bool UDestructionComponent::TryGetController()
{
	UWorld* world = GetWorld();

	if (world == nullptr)
		return false;

	Controller = world->GetFirstPlayerController();
	if (Controller == nullptr)
		return false;

	return true;
}

