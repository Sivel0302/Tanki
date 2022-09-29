// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "TankPawn.h"
#include "Turret.h"
#include "Projectile.h"
#include <DrawDebugHelpers.h>

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
	FireFire();

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	FireFire();

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::ReloadSpecial, 1 / FireRate, false);
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

void ACannon::ReloadSpecial()
{
	bReadyToFire = true;
	if (FireKolvoSpecial > 1) {
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::FireSpecial, 1 / FireRateSpecial, true, 1 / FireRateSpecial);
		FireKolvoSpecial--;
		bReadyToFireSpecial = false;
	}
	else {
		FireKolvoSpecial = FireKolvoSpecialSave;
		bReadyToFireSpecial = true;
	}
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::FireFire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile")));
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation(), spawnParams);
		if (projectile)
		{
			projectile->Start();
		}
	}
	else if (CannonType == ECannonType::FireProjectile2)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile2")));
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation(), spawnParams);
		if (projectile)
		{
			projectile->Start();
		}
	}
	else /*FireTrace*/
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace")));
		FHitResult hitResult;
		FCollisionQueryParams traceParams;
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector Start = ProjectileSpawnPoint->GetComponentLocation();
		FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Purple, false, 1.0f, 0, 5.0f);
			/*if (hitResult.Actor.Get())
			{
				hitResult.Actor.Get()->Destroy();
			}*/
			if (hitResult.Actor.Get())
			{
				IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(hitResult.Actor.Get());
				if (DamageTakerActor)
				{
					FDamageData damageData;
					damageData.DamageValue = FireDamage;
					damageData.Instigator = GetOwner();
					damageData.DamageMaker = this;
					DamageTakerActor->TakeDamage(damageData);
				}
				else
				{
					hitResult.Actor.Get()->Destroy();
				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 1.0f, 0, 5.0f);
		}
	}

}

