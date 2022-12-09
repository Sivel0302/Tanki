// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurrentObjectives.h"
#include "Quest.h"
#include "Components/ActorComponent.h"
#include "QuestListComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestListComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestAction, AQuest *);

public:
	// Sets default values for this component's properties
	UQuestListComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AQuest*> AcceptedQuests;
	UPROPERTY()
	AQuest* ActiveQuest;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCurrentObjectives> CurrentObjectivesWidgetClass;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void AddQuest(AQuest* Quest);
	const TArray<AQuest*>& GetQuests();
	AQuest* GetActiveQuest() const;
	void SetActiveQuest(AQuest* Quest);
	
	FOnQuestAction OnActiveQuestChanged;
};
