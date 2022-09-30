// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKI_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveRate = 0.005f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float Damage = 1.0f;

	FTimerHandle MoveTimer;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	class ACannon* Cannon;
	class ATankPawn* TankPawn;
	class AActor* Owner;

	void Start();

protected:
	virtual void BeginPlay() override;

	void Move();

};
