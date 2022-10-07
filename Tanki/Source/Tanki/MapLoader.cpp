// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLoader.h"
#include <Components/PointLightComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AMapLoader::AMapLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ActivatedLights"));
	ActivatedLight->SetupAttachment(sceneComp);

	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("DeactivatedLights"));
	DeactivatedLight->SetupAttachment(sceneComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMapLoader::OnTriggerOverlapBegin);

	//SetActiveLights();

}
void AMapLoader::BeginPlay()
{
	Super::BeginPlay();

	SetActivatedLights();

}


void AMapLoader::SetActivatedLights()
{
	ActivatedLight->SetHiddenInGame(!IsActivated);
	DeactivatedLight->SetHiddenInGame(IsActivated);

}

void AMapLoader::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsActivated)
		return;
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OtherActor == PlayerPawn)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}

}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	IsActivated = NewIsActivated;
	SetActivatedLights();
}


