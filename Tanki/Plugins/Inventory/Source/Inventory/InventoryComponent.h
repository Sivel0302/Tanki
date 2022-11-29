// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
    UPROPERTY(EditAnywhere)
    TMap<int, FInventorySlotInfo> Items;

public:
    FInventorySlotInfo * GetItem(int SlotIndex);
    void SetItem(int SlotIndex, const FInventorySlotInfo& Item);
    void ClearItem(int SlotIndex);
    const TMap<int, FInventorySlotInfo>& GetItems();
    int GetItemsNum();


};
