// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include <Components/BoxComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include <GameFramework/Actor.h>
#include "Cannon.h"
#include <Kismet/KismetMathLibrary.h>
#include "HealthComponent.h"
#include "IScorable.h"
#include <DrawDebugHelpers.h>

// Sets default values
ATurret::ATurret() : AParentPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	HealthComponent->OnDie.AddUObject(this, &ATurret::Destroyed);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATurret::DamageTaked);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
	{
		BodyMesh->SetStaticMesh(bodyMeshTemp);
	}
	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
	{
		TurretMesh->SetStaticMesh(turretMeshTemp);
	}


}

void ATurret::TakeDamage(FDamageData DamageData)
{	
	HealthComponent->TakeDamage(DamageData);
}

int ATurret::GetScore()
{
	return AddScore;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	//SetupCannon(CannonClass);
	
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
	
}

void ATurret::Targeting()
{
	if (!PlayerPawn)
	{
		return;
	}
	if (IsPlayerInRange() && IsPlayerSeen())
	{
		RotateToPlayer();
		if (CanFire())
		{
			Fire();
		}
	}
}

void ATurret::Destroyed()
{
	if (Cannon) {
		Cannon->Destroy();
	}
	Destroy();
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currentRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currentRotation, targetRotation, TargetingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return (aimAngle <= Accurency);

}

//void ATurret::Fire()
//{
//	if (Cannon)
//	{
//		if (Patrons > 0 && Cannon->IsReadyToFire())
//		{
//			Cannon->Fire();
//			Patrons--;
//		}
//	}
//}

//void ATurret::SetupCannon()
//{
//	if (!CannonClass)
//	{
//		return;
//	}
//	FActorSpawnParameters params;
//	params.Owner = this;
//	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
//	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//}


void ATurret::DamageTaked(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage: %f, health: %f"), *GetName(), Value, HealthComponent->GetHealth());
}

bool ATurret::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = GetEyesPosition();
	FHitResult hitResult;
	FCollisionQueryParams params;
	params.bTraceComplex = true;
	params.AddIgnoredActor(this);
	params.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, params))
	{
		AActor* hitActor = hitResult.GetActor();
		if (hitActor) {
			if (hitActor == PlayerPawn)
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Red, false, 0.5f, 0, 10);
				return true;
			}
			else
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Green, false, 0.5f, 0, 10);
				return false;
			}
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Black, false, 0.5f, 0, 10);
	return false;
}

FVector ATurret::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

