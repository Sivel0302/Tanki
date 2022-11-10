// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "FruitDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class TANKI_API UFruitDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	FText FruitName;
};
