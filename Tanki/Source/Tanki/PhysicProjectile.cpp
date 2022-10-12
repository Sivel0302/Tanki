// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicProjectile.h"
#include "PhysicsComponent.h"
#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h>
#include "DamageTaker.h"
#include "GameStructs.h"

APhysicProjectile::APhysicProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT("PhysicsComponent"));

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);
}

void APhysicProjectile::Start()
{
	MoveVector = GetActorForwardVector() * MovementSpeed;
	CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(),
		MoveVector, MaxTimeSimulation, TimeStep, 0);
	if (bShowTrajectory)
	{
		for (FVector position : CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5, 8, FColor::Purple, true, 1, 0, 2);
		}
	}
	TragectoryPointIndex = 0;
	TrailEffect->ActivateSystem();

	Super::Start();
}

void APhysicProjectile::Move()
{
	FVector currentMoveVector = CurrentTrajectory[TragectoryPointIndex] - GetActorLocation();
	currentMoveVector.Normalize();

	FVector newLocation = GetActorLocation() + currentMoveVector * MovementSpeed * MoveRate;
	SetActorLocation(newLocation);

	if (FVector::Distance(newLocation, CurrentTrajectory[TragectoryPointIndex]) <= MovementAccurency)
	{
		TragectoryPointIndex++;
		if (TragectoryPointIndex >= CurrentTrajectory.Num())
		{
			Explode();
			Destroy();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
				CurrentTrajectory[TragectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}
}

void APhysicProjectile::Explode()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);

	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";

	TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;

	bool bSweepResult = GetWorld()->SweepMultiByChannel(AttackHit, startPos, endPos, Rotation,
		ECollisionChannel::ECC_Visibility, Shape,params);

	//GetWorld()->DebugDrawTraceTag = "Explode Trace";
	DrawDebugSphere(GetWorld(), startPos, ExplodeRadius, 5, FColor::Green, false, 2.0f);

	if (bSweepResult)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
			{
				continue;
			}

			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
			if (damageTakerActor)
			{
				FDamageData damageData;
				damageData.DamageValue = Damage;
				damageData.Instigator = GetOwner();
				damageData.DamageMaker = this;

				damageTakerActor->TakeDamage(damageData);
			}
			else
			{
				UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
				if (mesh)
				{
					if (mesh->IsSimulatingPhysics())
					{
						FVector forceVector = otherActor->GetActorLocation() - GetActorLocation();
						forceVector.Normalize();
						mesh->AddImpulse(forceVector * PushForce, NAME_None, true);
					}
				}
			}
		}
	}
}
