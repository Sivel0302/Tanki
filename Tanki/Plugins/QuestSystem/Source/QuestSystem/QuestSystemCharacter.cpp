// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemCharacter.h"


// Sets default values
AQuestSystemCharacter::AQuestSystemCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQuestSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

