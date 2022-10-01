// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include <UObject/NoExportTypes.h>


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector pawnLocation = TankPawn->GetActorLocation();
	MovementAccurency = TankPawn->GetMovementAccurency();
	TArray<FVector> points = TankPawn->GetPatrollingPoints();
	for (FVector point : points)
	{
		PatrollingPoints.Add(point + pawnLocation);
	}
	PatrollingIndex = 0;
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TankPawn->MoveForward(1);

	float rotationValue = GetRotationValue();
	TankPawn->RotateRight(rotationValue);

	Targeting();
}

float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPoints[PatrollingIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	float distance = FVector::Distance(currentPoint, pawnLocation);
	//UE_LOG(LogTemp, Warning, TEXT("distance: %f"), distance);
	if (distance <= MovementAccurency)
	{
		PatrollingIndex++;
		if (PatrollingIndex >= PatrollingPoints.Num())
			PatrollingIndex = 0;
	}

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	//DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	float rotationValue = 0;
	if (forwardAngle > 5)
	{
		rotationValue = 1;
	}
	if (rightAngle > 90)
	{
		rotationValue = -rotationValue;
	}
	//UE_LOG(LogTemp, Warning, TEXT("AI Rotation forwardAngle: %f rightAngle: %f rotationValue:% f"), forwardAngle, rightAngle, rotationValue);
	return rotationValue;
}

void ATankAIController::Targeting()
{
	if (!TankPawn)
	{
		return;
	}

	if (IsPlayerInRange()) {
		if (CanFire())
		{
			Fire();
		}
		else
		{
			RotateToPlayer();
		}
	}
}

void ATankAIController::RotateToPlayer()
{
	TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

void ATankAIController::Fire()
{
	TankPawn->Fire();
}

bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;

}

bool ATankAIController::CanFire()
{
	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float AimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return AimAngle <= Accurency;

}

bool ATankAIController::IsPlayerSeen()
{
	return false;
}
