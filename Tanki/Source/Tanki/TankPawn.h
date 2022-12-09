// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "GameStructs.h"
#include "IScorable.h"
#include "ParentPawn.h"
#include <Camera/CameraComponent.h>
#include <UObject/NoExportTypes.h>
#include <Templates/SubclassOf.h>
#include <Particles/ParticleSystemComponent.h>

#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryManagerComponent.h"
#include "QuestSystem/InteractionComponent.h"
#include "QuestSystem/QuestList.h"
#include "TankPawn.generated.h"

class UstaticMeshComponent;
class ACannon;
class ATargetPoint;
UCLASS()
class TANKI_API ATankPawn : public AParentPawn, public IDamageTaker, public IIScorable
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

	virtual void Fire() override;
	void FireSpecial();

	UFUNCTION()
		virtual int GetScore() override;


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
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIComponents")
		float MovementAccurency = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIComponents", Meta = (MakeEditWidget = true))
		TArray<ATargetPoint*> PatrollingPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;


public:
	FVector GetTurretForwardVector() const { return TurretMesh->GetForwardVector(); }
	UFUNCTION()
		float GetMovementAccurency() const { return MovementAccurency; };
	UFUNCTION()
		TArray<FVector> GetPatrollingPoints();

	void SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);

	UFUNCTION()
		void RotateTurretTo(FVector TargetPosition);
	FVector GetEyesPosition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 100.0f;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
		int Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int AddScore = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cannon")
		int CannonNumber = 1;

	//инвентарь
	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent * InventoryComponent;
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent * InventoryManagerComponent;

	//квесты
	UPROPERTY(EditDefaultsOnly)
	UQuestListComponent * QuestListComponent;
	UFUNCTION(BlueprintCallable)
	void ToggleQuestListVisibility();
	UPROPERTY()
	UQuestList * QuestList;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestList> QuestListClass;

private:
	class ATankController* TankController;

	float ForwardMoveAxisValue = 0.0f;
	float RightMoveAxisValue = 0.0f;

	float RotateRightAxisValue = 0.0f;
	float CurrentRightAxisValue = 0.0f;
	float RotateInterpolationKey = 0.1f;
	float TurretInterpolationKey = 0.5f;



};
