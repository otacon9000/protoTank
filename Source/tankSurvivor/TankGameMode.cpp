// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "EnemyController.h"

ATankGameMode::ATankGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATankGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer <= 0.0f)
	{
		float DifficultyPercentage = FMath::Min(GameTimer / TIME_TO_MIN, 1.0f);
		EnemyTimer = MAX_INTERVAL - (MAX_INTERVAL - MIN_INTERVAL) * DifficultyPercentage;

		UE_LOG(LogTemp, Warning, TEXT("Enemy Timer = %f"), EnemyTimer);

		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = FVector(2100.0f, FMath::RandRange(-30.0f, 3200.0f), 150.0f);
			World->SpawnActor<AEnemyController>(Enemy_BP, Location, FRotator::ZeroRotator);
		}
	}

}

void ATankGameMode::AddScore()
{
	Score += 10;
	//update UI 
}
