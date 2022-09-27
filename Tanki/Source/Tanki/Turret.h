// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKI_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Targeting();
	void Destroyed();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();

	void SetupCannon();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* HitCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CannonSetupPoint;

	UPROPERTY()
		ACannon* Cannon;
	UPROPERTY()
		APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float TargetingRate = 0.005f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 40;

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		int Patrons = 50;
};
