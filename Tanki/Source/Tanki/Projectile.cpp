// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <Components/SceneComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "DamageTaker.h"
#include "IScorable.h"
#include <GameFramework/Actor.h>
#include "Cannon.h"
#include "TankPawn.h"
#include "Turret.h"
#include <Particles/ParticleSystemComponent.h>
//#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceeneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceeneComp;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(SceeneComp);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(SphereCollision);

	/*TakeDamageEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TakeDamageEffect"));
	TakeDamageEffect->SetAutoActivate(false);
	TakeDamageEffect->SetupAttachment(ProjectileMesh);*/


}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Cannon = Cast<ACannon>(GetOwner());
	TankPawn = Cast<ATankPawn>(Cannon->GetOwner());
	Owner = Cannon->GetOwner();
}

void AProjectile::Move()
{
	FVector movePosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(movePosition);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
	OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
	bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (Owner) {
			if (OtherActor != Owner) {
				IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(OtherActor);
				IIScorable* ScoreActor = Cast<IIScorable>(OtherActor);
				if (DamageTakerActor)
				{
					FDamageData damageData;
					damageData.DamageValue = Damage;
					damageData.Instigator = GetOwner();
					damageData.DamageMaker = this;
					DamageTakerActor->TakeDamage(damageData);
					if (ScoreActor && TankPawn)
					{
						if (OtherActor->IsActorBeingDestroyed())
						{
							TankPawn->Score += ScoreActor->GetScore();
							GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Score: %d"), TankPawn->Score));
						}
					}
				}
				else
				{
					//OtherActor->Destroy();
				}
				//TakeDamageEffect->ActivateSystem(true);
				//if (TakeDamageEffect)
				//{
				//	//FVector ExplosionLocation = ProjectileMesh->GetComponentLocation();
				//	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TakeDamageEffect, ExplosionLocation);
				//}
				Destroy();
			}
		}
	}
}




