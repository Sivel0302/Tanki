// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include <Camera/CameraShakeBase.h>
#include "Cannon.generated.h"

UCLASS()
class TANKI_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	void Fire();
	void FireSpecial();
	void Reload();
	void ReloadSpecial();
	bool IsReadyToFire();

	void FireFire();

	FTimerHandle ReloadTimer;
	FTimerHandle BurstTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		TSubclassOf<class UCameraShakeBase> CameraShake;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
		UParticleSystemComponent* ShotEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
		UAudioComponent* ShotSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRateSpecial = 6.0f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		int FireKolvoSpecial = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1.0f;



private:
	class ATankPawn* TankPawn;
	class AActor* Owner;

	bool bReadyToFire = false;

	int FireKolvoSpecialSave = FireKolvoSpecial;
public:
	bool bReadyToFireSpecial = true;

};
