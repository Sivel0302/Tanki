// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include "HealthComponent.h"
#include <Components/ArrowComponent.h>
#include "TankPawn.h"
#include <Engine/TargetPoint.h>
#include "DamageTaker.h"
#include "MapLoader.h"
#include <Particles/ParticleSystem.h>
#include <Particles/ParticleSystemComponent.h>
#include <Engine/StaticMesh.h>
#include <Materials/Material.h>
#include <Materials/MaterialInterface.h>
#include "TankFactory.generated.h"

UCLASS()
class TANKI_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankFactory();

	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float DamageValue);
	void SpawnNewTank();
	void DieEffects();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BuildingMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMesh* DieMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UMaterialInterface* DieMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* TankSpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		TSubclassOf<ATankPawn> SpawnTankClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		float SpawnTankRate = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		TArray<ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLoader")
		AMapLoader* MapLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UParticleSystemComponent* SpawnEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UParticleSystem* DieEffect;
	class UParticleSystemComponent* Template;


};
