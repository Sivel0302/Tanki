// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <Components/ArrowComponent.h>
#include "HealthComponent.h"
#include "TankPawn.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
ATankFactory::ATankFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankSpawnPoint"));
	TankSpawnPoint->SetupAttachment(BuildingMesh);


	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);

	SpawnEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnEffect"));
	SpawnEffect->SetAutoActivate(false);
	SpawnEffect->SetupAttachment(TankSpawnPoint);

}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if (MapLoader)
		MapLoader->SetIsActivated(false);

	FTimerHandle SpawnTimer;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATankFactory::SpawnNewTank, SpawnTankRate, true, 2);

}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankFactory::Die()
{
	if (MapLoader)
		MapLoader->SetIsActivated(true);
	DieEffects();
	Destroy();
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());

}

void ATankFactory::SpawnNewTank()
{
	if (SpawnEffect)
	{
		SpawnEffect->ActivateSystem();
	}

	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass,
		spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	newTank->SetPatrollingPoints(TankWayPoints);
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);

}

void ATankFactory::DieEffects()
{
	if (DieEffect)
	{
		Template = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DieEffect, BuildingMesh->GetComponentLocation());
		//DestructionParticle->SetWorldScale3D(FVector(1.0, 1.0, 1.0) * 3.0);
		//GetStaticMeshComponent()->SetVisibility(false, true); // hide it
	}
}

