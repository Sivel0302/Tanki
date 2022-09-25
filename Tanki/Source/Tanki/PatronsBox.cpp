// Fill out your copyright notice in the Description page of Project Settings.


#include "PatronsBox.h"
#include <Delegates/Delegate.h>
#include "TankPawn.h"

// Sets default values
APatronsBox::APatronsBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	PatronsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PatronsMesh"));
	PatronsMesh->SetupAttachment(SceneComp);
	PatronsMesh->OnComponentBeginOverlap.AddDynamic(this, &APatronsBox::OnMeshOverlapBegin);
	PatronsMesh->SetCollisionProfileName(FName("OverlapAll"));
	PatronsMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PatronsMesh->SetGenerateOverlapEvents(true);

}

void APatronsBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		TankPawn->Patrons += Patrons;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Added %d patrons"), Patrons));
		Destroy();
	}
}


