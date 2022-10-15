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
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Destroyed);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATurret::DamageTaked);

	/*UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
	{
		BodyMesh->SetStaticMesh(bodyMeshTemp);
	}
	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
	{
		TurretMesh->SetStaticMesh(turretMeshTemp);
	}*/


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
	
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
	
}

void ATurret::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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

void ATurret::Targeting()
{
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
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
	DieEffects();
	Destroy();
}

void ATurret::RotateToPlayer()
{
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
		FRotator currentRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = currentRotation.Pitch;
		targetRotation.Roll = currentRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(currentRotation, targetRotation, TargetingSpeed));
	}
}

bool ATurret::IsPlayerInRange()
{
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
	}
	else
	{
		return false;
	}
}

bool ATurret::CanFire()
{
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		FVector targetingDir = TurretMesh->GetForwardVector();
		FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
		dirToPlayer.Normalize();

		float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
		return (aimAngle <= Accurency);
	}
	else
	{
		return false;
	}

}

void ATurret::DamageTaked(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage: %f, health: %f"), *GetName(), Value, HealthComponent->GetHealth());
}

bool ATurret::IsPlayerSeen()
{
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
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
	else
	{
		return false;
	}
}

FVector ATurret::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

