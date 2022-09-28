// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "GameStructs.h"
#include "TankPawn.generated.h"

class UstaticMeshComponent;
class ACannon;
UCLASS()
class TANKI_API ATankPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void RotateRight(float Value);

	void SetupCannon(TSubclassOf<ACannon> newCannon);
	void Fire();
	void FireSpecial();

	/*UFUNCTION(BlueprintCallable)
		class UHealthComponent* GetHealthComponent() const { return HealthComponent; }*/

	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData) override;
	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float Value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComponent;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxCollision;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		class UArrowComponent* CannonSetupPoint;

	UPROPERTY()
		ACannon* Cannon;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 100.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		int Patrons = 20;

private:
	class ATankController* TankController;

	float ForwardMoveAxisValue = 0.0f;
	float RightMoveAxisValue = 0.0f;

	float RotateRightAxisValue = 0.0f;
	float CurrentRightAxisValue = 0.0f;
	float RotateInterpolationKey = 0.1f;
	float TurretInterpolationKey = 0.5f;



};
