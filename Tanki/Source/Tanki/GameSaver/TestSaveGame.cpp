// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSaveGame.h"

void UTestSaveGame::AddEnemySaves(FSaveData SaveData)
{
	EnemySaves.Add(SaveData);
}

TArray<FSaveData> UTestSaveGame::GetEnemySaves()
{
	return EnemySaves;
}
