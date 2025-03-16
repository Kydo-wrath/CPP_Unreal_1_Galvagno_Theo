// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"

// Sets default values
ABasicPawn::ABasicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	m_CubeMesh->SetupAttachment(RootComponent);

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(RootComponent);
	m_Camera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	m_Camera->SetWorldRotation(FRotator(-45.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		m_CubeMesh->SetStaticMesh(CubeVisualAsset.Object);
		m_CubeMesh->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Can't find it"));

	RotationMaxSpeed = 200;
	MovementMaxSpeed = 200;

	MovementAcceleration = 10;
	RotationAcceleration = 10;

	MovementDeceleration = 30;
	RotationDeceleration = 30;

	MpreviousPawn = nullptr;
	MCurrentMovementSpeed = 0;
	MCurrentRotationSpeed = 0;
	MMovementInput = FVector::ZeroVector;

	AccelerateMovement = 0.0;
	AccelerateRotation = 0.0;

	DecelerateMovement = 0.0;
	DevelerateRotation = 0.0;

	RootRotation = RootComponent->GetComponentRotation();
}

// Called when the game starts or when spawned
void ABasicPawn::BeginPlay()
{
	//Pocess the cube when the scene begin
	
	Super::BeginPlay();
	
	//Get the world 
	UWorld* world = GetWorld();
	if (world == nullptr)
		return;

	//Get the current Player
	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr)
		return;

	//Save who is the base controller
	MpreviousPawn = controller->GetPawn();

	//Change controller
	controller->UnPossess();
	controller->Possess(this);
}

// Called every frame
void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateCube();
	SmoothMovement(MovementAcceleration,MovementDeceleration, DeltaTime);
	SmoothRotation(RotationAcceleration, RotationDeceleration, DeltaTime);
	MoveCubeDirection();

	if (MMovementInput.X < 0)
		NegateRotation = true;
	else if (MMovementInput.X > 0)
		NegateRotation = false;

	if (MMovementInput.Y < 0)
		NegateMovement = true;
	else if (MMovementInput.Y > 0)
		NegateMovement = false;
}

void ABasicPawn::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	SetMappingContext(true);
}

// Called to bind functionality to input
void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Exit, ETriggerEvent::Started, this, &ABasicPawn::ExitCube);

		EnhancedInputComponent->BindAction(Movement, ETriggerEvent::Triggered, this, &ABasicPawn::MoveInputOn);

		EnhancedInputComponent->BindAction(Movement, ETriggerEvent::Completed, this, &ABasicPawn::MoveInputOff);
	}
}

void ABasicPawn::SetMappingContext(bool value)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (value)
				Subsystem->AddMappingContext(CubeControlContext, 0);
			else
				Subsystem->RemoveMappingContext(CubeControlContext);
		}
	}
}

void ABasicPawn::ExitCube(const FInputActionValue& value)
{
	// Unpocess the cube
	AController* controller = GetController();
	controller->UnPossess();
	controller->Possess(MpreviousPawn);

	//Make sure to not keep the cube control after change
	SetMappingContext(false);

	//Reset the previous controller
	MpreviousPawn = nullptr;
}

void ABasicPawn::MoveInputOn(const FInputActionValue& value)
{
	MMovementInput = value.Get<FVector>();
}

void ABasicPawn::MoveInputOff(const FInputActionValue& value)
{
	MMovementInput = FVector::ZeroVector;

}

void ABasicPawn::MoveCubeDirection()
{

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = RootComponent->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		if (!NegateMovement)
			RootComponent->AddRelativeLocation(ForwardDirection * MCurrentMovementSpeed);
		else
			RootComponent->AddRelativeLocation(ForwardDirection * -MCurrentMovementSpeed);


		//UE_LOG(LogTemp, Warning, TEXT("Moves value : %s"), *ForwardDirection.ToString());

	}
}

void ABasicPawn::RotateCube()
{

	if (!NegateRotation)
		RootRotation.Yaw = MCurrentRotationSpeed;
	else
		RootRotation.Yaw = -MCurrentRotationSpeed;

	RootComponent->AddWorldRotation(RootRotation);
}

void ABasicPawn::SmoothMovement(const float& MoveAccelerationValue, const float& MovedecelerationValue, const float deltaTime)
{
	if (MMovementInput.Y == 0)
	{
		DecelerateMovement = MCurrentMovementSpeed / MovementMaxSpeed - deltaTime * MovedecelerationValue / MovementMaxSpeed;

		if (DecelerateMovement < 0.0)
			DecelerateMovement = 0;

		MCurrentMovementSpeed = FMath::Lerp(0, MovementMaxSpeed, DecelerateMovement);
	}
	else
	{
		AccelerateMovement = MCurrentMovementSpeed / MovementMaxSpeed + deltaTime * MoveAccelerationValue / MovementMaxSpeed;

			if (AccelerateMovement >= 1)
				AccelerateMovement = 1;

		MCurrentMovementSpeed = FMath::Lerp(0, MovementMaxSpeed, AccelerateMovement);
	}
}

void ABasicPawn::SmoothRotation(const float& RotationAccelerationValue, const float& RotationdecelerationValue, const float deltaTime)
{
	if (MMovementInput.X == 0)
	{
		DevelerateRotation = MCurrentRotationSpeed / RotationMaxSpeed - deltaTime * RotationdecelerationValue / RotationMaxSpeed;

		if (DevelerateRotation < 0.0)
			DevelerateRotation = 0;

		MCurrentRotationSpeed = FMath::Lerp(0, RotationMaxSpeed, DevelerateRotation);
	}
	else
	{
		AccelerateRotation = MCurrentRotationSpeed / RotationMaxSpeed + deltaTime * RotationAccelerationValue / RotationMaxSpeed;

		if (AccelerateRotation >= 1)
			AccelerateRotation = 1;

		MCurrentRotationSpeed = FMath::Lerp(0, RotationMaxSpeed, AccelerateRotation);
	}
}

