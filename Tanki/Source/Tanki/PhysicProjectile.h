// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "PhysicsComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TANKI_API APhysicProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:
	APhysicProjectile();

	virtual void Start() override;

protected:
	virtual void Move() override;
	void Explode();
	void TakeDamagePawn(AActor* otherActor);
	void TakeImpulse(AActor* otherActor);
	/*UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult);*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UPhysicsComponent* PhysicsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* TrailEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementParams")
		float MovementAccurency = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementParams")
		float MaxTimeSimulation = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementParams")
		float TimeStep = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementParams")
		float MovementSpeed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementParams")
		bool bShowTrajectory = true;

	UPROPERTY(EditAnywhere, Category = "ExplodeParams")
		float ExplodeRadius = 50;
	UPROPERTY(EditAnywhere, Category = "ExplodeParams")
		bool bExplode = true;

	UPROPERTY(BlueprintReadWrite, Category = "MovementParams")
		FVector MoveVector;
	UPROPERTY(BlueprintReadWrite, Category = "MovementParams")
		TArray<FVector> CurrentTrajectory;
	UPROPERTY(BlueprintReadWrite, Category = "MovementParams")
		int32 TragectoryPointIndex;



};
