// Fill out your copyright notice in the Description page of Project Settings.


#include "SavingsManager.h"

#include "Kismet/GameplayStatics.h"

void USavingsManager::Init()
{
	CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));

	FString ProjectDirectory = FPaths::ProjectDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectDirectory: %s"), *ProjectDirectory);
}

bool USavingsManager::DoesSaveGameExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void USavingsManager::LoadGame(const FString& SlotName)
{
	//CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0,
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &USavingsManager::OnGameLoadedFromSlotHandle));
}

void USavingsManager::SaveCurrentGame(const FString& SlotName)
{
	//UGameplayStatics::SaveGameToSlot(CurrentGameObject, SlotName, 0);

	UGameplayStatics::AsyncSaveGameToSlot(CurrentGameObject, SlotName, 0,
		FAsyncSaveGameToSlotDelegate::CreateUObject(this, &USavingsManager::OnGameSavedToSlotHandle));

}

void USavingsManager::OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentGameObject = Cast<UTestSaveGame>(SaveGame);
    if (OnGameLoadedFromSlot.IsBound())
    {
		OnGameLoadedFromSlot.Broadcast(SlotName);
    }

}

void USavingsManager::OnGameSavedToSlotHandle(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (OnGameSavedToSlot.IsBound())
	{
		OnGameSavedToSlot.Broadcast(SlotName);
	}
}
