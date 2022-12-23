// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include <Kismet/KismetMathLibrary.h>
#include "Cannon.h"
#include <Components/ArrowComponent.h>
#include <Containers/UnrealString.h>
#include "HealthComponent.h"
#include "IScorable.h"
#include <Components/SceneComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include <Engine/TargetPoint.h>

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameSaver/MyGameInstance.h"

// Sets default values
ATankPawn::ATankPawn() : AParentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);*/


	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankPawn::DamageTaked);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	/*HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);*/

	//инвентарь
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	InventoryManagerComponent =	CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
	
	//квесты
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->SetupAttachment(BoxCollision);
	QuestListComponent = CreateDefaultSubobject<UQuestListComponent>("QuestListComponent");
	
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<ATankController>(GetController());

	//инвентарь
	InventoryManagerComponent->Init(InventoryComponent);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MoveForward
	FVector currentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	//UE_LOG(LogTemp, Warning, TEXT("ForwardVector: %s"), *ForwardVector.ToString());
	FVector RightVector = GetActorRightVector();
	//UE_LOG(LogTemp, Warning, TEXT("RightVector: %s"), *RightVector.ToString());
	FVector movePosition = currentLocation + ForwardVector * MovementSpeed * ForwardMoveAxisValue * DeltaTime
		+ RightVector * MovementSpeed * RightMoveAxisValue * DeltaTime;
	SetActorLocation(movePosition);

	//BodyRotation
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, RotateRightAxisValue, RotateInterpolationKey);
	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue %f, RotateRightAxisValue %f"), CurrentRightAxisValue, RotateRightAxisValue);

	float yawRotation = CurrentRightAxisValue * RotationSpeed * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	yawRotation += currentRotation.Yaw; // yawRotation = currentRotation + yawRotation;
	FRotator newRotation = FRotator(0.0f, yawRotation, 0.0f);
	SetActorRotation(newRotation);

	//TurretRotation
	if (TankController)
	{
		//if (Cannon->CameraShake->)
		//{
			FVector MousePos = TankController->GetMousePos();
			RotateTurretTo(MousePos);
		//}
	}

}


TArray<FVector> ATankPawn::GetPatrollingPoints()
{
	TArray<FVector> points;
	for (ATargetPoint* point : PatrollingPoints)
	{
		if (point)
		{
			points.Add(point->GetActorLocation());
		}
	}
	return points;
}

void ATankPawn::SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator turretRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = turretRotation.Pitch;
	targetRotation.Roll = turretRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(targetRotation, turretRotation, TurretInterpolationKey));
}


FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATankPawn::SaveInventory()
{
	auto GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SaveManager->CurrentGameObject->Inventory = InventoryComponent->Items;
	}
}

void ATankPawn::LoadInventory()
{
	auto GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		 InventoryComponent->Items = GameInstance->SaveManager->CurrentGameObject->Inventory;
	}
}

void ATankPawn::ToggleQuestListVisibility()
{
	APlayerController * PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (QuestList )
	{
		QuestList->RemoveFromParent();
		QuestList = nullptr;
		if (PC)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
			PC->bShowMouseCursor = false;
		}
	}
	else
	{
		if (QuestListClass)
		{
			QuestList = CreateWidget<UQuestList>(GetWorld(), QuestListClass);
			QuestList->Init(QuestListComponent);
			QuestList->AddToViewport();
			if (PC)
			{
				UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC);
				PC->bShowMouseCursor = true;
			}
		}
	}
}

void ATankPawn::MoveForward(float Value)
{
	ForwardMoveAxisValue = Value;
}
void ATankPawn::MoveRight(float Value)
{
	RightMoveAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::Fire()
{
	Super::Fire();
	if (TankController) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Patrons: %d"), Patrons));
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		if (Patrons >= Cannon->FireKolvoSpecial && Cannon->bReadyToFireSpecial)
		{
			Cannon->FireSpecial();
			Patrons -= Cannon->FireKolvoSpecial;
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Patrons: %d"), Patrons));
		}
	}
}


int ATankPawn::GetScore()
{
	return AddScore;
}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankPawn::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	DieEffects();
	Destroy();
}

void ATankPawn::DamageTaked(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage: %f, health: %f"), *GetName(), Value, HealthComponent->GetHealth());
}


