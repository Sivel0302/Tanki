// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "TankPawn.h"

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
	TankPawn = Cast<ATankPawn>(GetOwner());
	Reload();
	
}

void ACannon::Fire()
{
	if (TankPawn->Patrons > 0)
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

		TankPawn->Patrons--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Patrons: %d"), TankPawn->Patrons));
	}
}

void ACannon::FireSpecial()
{
	if (TankPawn->Patrons > 0)
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

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::ReloadSpecial, 1 / FireRate, false);

		TankPawn->Patrons--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Patrons: %d"), TankPawn->Patrons));
	}
}

void ACannon::Reload()
{
	bReadyToFire = true;
	//GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Fire, 1 / FireRate, true, 1 / FireRate);
}

void ACannon::ReloadSpecial()
{
	bReadyToFire = true;
	if (FireKolvoSpecial > 1) {
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::FireSpecial, 1 / FireRateSpecial, true, 1 / FireRateSpecial);
		FireKolvoSpecial--;
	}
	else {
		FireKolvoSpecial = FireKolvoSpecialSave;
	}
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

