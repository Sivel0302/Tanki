// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "InteractionObjective.h"
#include "LocationObjective.h"


// Sets default values
AQuest::AQuest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuest::UpdateLocation()
{
	AActor * ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQuest::TakeQuest(AActor* Character)
{
	if (bIsTaken)
	{
		return;
	}
	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		if (Objectives[i])
		{
			Objectives[i]->ActivateObjective(Character);
			Objectives[i]->bCanBeCompleted = !bKeepObjectivesOrder || i == 0;
			Objectives[i]->OnObjectiveCompleted.AddUObject(this,
			&AQuest::OnObjectiveCompleted);
		}
	}
	bIsTaken = true;
}

void AQuest::AddLocationObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));
}

void AQuest::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));
}

TArray<UObjective*> AQuest::GetObjectives()
{
	return Objectives;
}

bool AQuest::IsCompleted()
{
	for (UObjective* Objective : Objectives)
	{
		if (!Objective->bIsCompleted)
		{
			return false;
		}
	}
	return true;
}

void AQuest::OnObjectiveCompleted(UObjective* Objective)
{
	bIsCompleted = IsCompleted();
	if (bKeepObjectivesOrder)
    {
	    int32 ObjectiveIndex;
	    if (Objectives.Find(Objective, ObjectiveIndex) && Objectives.IsValidIndex(ObjectiveIndex + 1))
	    {
			Objectives[ObjectiveIndex + 1]->bCanBeCompleted = true;
	    }
    }
    if (OnQuestStatusUpdated.IsBound())
    {
		OnQuestStatusUpdated.Broadcast(this);
    }

}

