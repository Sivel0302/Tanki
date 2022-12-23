// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Inventory/InventoryItem.h"
#include "Tanki/GameStructs.h"
#include "TestSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TANKI_API UTestSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    float TestFloat;

	//Игрок
	UPROPERTY(BlueprintReadWrite)
	float PlayerHealth;
	UPROPERTY(BlueprintReadWrite)
	int PlayerPatrons;

	//враги
	TArray<FSaveData> EnemySaves;
	//UFUNCTION(BlueprintCallable)
	void AddEnemySaves(FSaveData SaveData);
	TArray<FSaveData> GetEnemySaves();

	//инвентарь
	UPROPERTY(EditAnywhere)
	TMap<int, FInventorySlotInfo> Inventory;

};
