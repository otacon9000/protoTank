// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankController.generated.h"

UCLASS()
class TANKSURVIVOR_API ATankController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	float speed = 10.0f;
	
	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class ABulletController> BulletBP;



	void MoveAxisX(float AxisValue);
	void MoveAxisY(float AxisValue);
	void OnShoot();
	void OnRestart();

	FVector CurrentVelocity;

	bool Died;

	UFUNCTION()
	void OnTriggerEnter(class UPrimitiveComponent* OverlappedComponent, 
		class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};