// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestSaveGame.h"
#include "UObject/Object.h"
#include "SavingsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFromSlotAction, const FString&, SlotName);

/**
 * 
 */
UCLASS()
class TANKI_API USavingsManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExist(const FString& SlotName);
	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName);
	UFUNCTION(BlueprintCallable)
	void SaveCurrentGame(const FString& SlotName);

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnGameFromSlotAction OnGameLoadedFromSlot;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnGameFromSlotAction OnGameSavedToSlot;

	UFUNCTION(BlueprintCallable)
    const TArray<FString>& GetExistingSavedSlots() const;

	
public:
	UPROPERTY(BlueprintReadWrite)
	UTestSaveGame * CurrentGameObject;

protected:
	void OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);
	void OnGameSavedToSlotHandle(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	TArray<FString> ExistingSavedSlots;
	const FString ExistingSavedSlotsFilePath = "existing_slots.txt";
	void CacheExistingSavedSlotsInfo();
};
