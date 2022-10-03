// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentPawn.h"
#include "Cannon.h"
#include <Engine/EngineTypes.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/Actor.h>
#include <Particles/ParticleSystemComponent.h>

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

	DieEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DieEffect"));
	DieEffect->SetAutoActivate(false);
	DieEffect->SetupAttachment(BodyMesh);

}

// Called when the game starts or when spawned
void AParentPawn::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);	
}

// Called every frame
//void AParentPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

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

//// Called to bind functionality to input
//void AParentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

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
