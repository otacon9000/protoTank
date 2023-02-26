// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "Components/BoxComponent.h"
#include "BulletController.h"

// Sets default values
ATankController::ATankController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATankController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!currentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (speed * currentVelocity * DeltaTime);
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void ATankController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATankController::MoveAxisX);
	InputComponent->BindAxis("MoveY", this, &ATankController::MoveAxisY);
	InputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ATankController::OnShoot);

}

void ATankController::MoveAxisX(float axisValue)
{
	currentVelocity.X = axisValue * 100.0f;
}

void ATankController::MoveAxisY(float axisValue)
{
	currentVelocity.Y = axisValue * 100.0f;
}

void ATankController::OnShoot()
{
	UWorld* World = GetWorld();

	if (World)
	{
		FVector Location = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Location, %f %f"), Location.X, Location.Y);

		World->SpawnActor<ABulletController>(bulletBP, Location, FRotator::ZeroRotator);
	}

}
