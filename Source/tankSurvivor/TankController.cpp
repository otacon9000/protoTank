// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "Components/BoxComponent.h"
#include "BulletController.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATankController::ATankController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATankController::OnTriggerEnter);


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

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (speed * CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
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

void ATankController::MoveAxisX(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

void ATankController::MoveAxisY(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}

void ATankController::OnShoot()
{
	UWorld* World = GetWorld();

	if (World)
	{
		FVector Location = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Location, %f %f"), Location.X, Location.Y);

		World->SpawnActor<ABulletController>(BulletBP, Location, FRotator::ZeroRotator);
	}

}

void ATankController::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass()))
	{
		Died = true;
		this->SetActorHiddenInGame(true);

		//pause the game
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}



