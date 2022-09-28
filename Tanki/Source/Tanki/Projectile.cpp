// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <Components/SceneComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "DamageTaker.h"

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
	//Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);


}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
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
		IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (DamageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = GetOwner();
			damageData.DamageMaker = this;
			DamageTakerActor->TakeDamage(damageData);
		}
		else
		{
			OtherActor->Destroy();
		}
		Destroy();
	}

	//OtherActor->Destroy();
	Destroy();
}




