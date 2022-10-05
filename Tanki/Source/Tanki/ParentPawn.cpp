// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentPawn.h"
#include "Cannon.h"
#include <Engine/EngineTypes.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/Actor.h>
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AParentPawn::AParentPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void AParentPawn::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);	
}

void AParentPawn::SetupCannon(TSubclassOf<ACannon> newCannon)
{
	if (!newCannon)
	{
		return;
	}

	if (Cannon)
	{
		Cannon->Destroy();
	}

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannon, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CannonClass = newCannon;
}

void AParentPawn::DieEffects()
{
	if (DieEffect)
	{
		Template = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DieEffect, BodyMesh->GetComponentLocation());
		//DestructionParticle->SetWorldScale3D(FVector(1.0, 1.0, 1.0) * 3.0);
		//GetStaticMeshComponent()->SetVisibility(false, true); // hide it
	}
}

void AParentPawn::Fire()
{
	if (Cannon)
	{
		if (Patrons > 0 && Cannon->IsReadyToFire())
		{
			Cannon->Fire();
			Patrons--;
		}
	}
}
