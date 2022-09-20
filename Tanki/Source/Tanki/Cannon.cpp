// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);

}


// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	
}

//// Called every frame
//void ACannon::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace")));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::Reload()
{
	bReadyToFire = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Fire, 1 / FireRate, true, 1 / FireRate);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

