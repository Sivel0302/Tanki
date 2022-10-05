// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPawn.h"
#include <GameFramework/Pawn.h>
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKI_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		class ATankPawn* TankPawn;
	UPROPERTY()
		class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIParams" , Meta = (MakeEditWidget = true))
		TArray<FVector> PatrollingPoints;

	int32 PatrollingIndex = 0;
	float MovementAccurency;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
		float MovementAccurency;*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10;

	float GetRotationValue();
	void Targeting();
	void RotateToPlayer();
	void Fire();
	bool IsPlayerInRange();
	bool CanFire();
	bool IsPlayerSeen();

	void Initialize();


};
