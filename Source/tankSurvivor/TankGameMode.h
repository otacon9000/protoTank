// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKSURVIVOR_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

	float MIN_INTERVAL = 0.5f;
	float MAX_INTERVAL = 2.0f;
	float TIME_TO_MIN = 30.0f;

public:
	ATankGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AddScore();

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class AEnemyController> Enemy_BP;

	float EnemyTimer;
	float GameTimer;

protected:
	int Score = 0;
	
};
