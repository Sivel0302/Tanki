// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FInventorySlotInfo* UInventoryComponent::GetItem(int SlotIndex)
{
	return Items.Find(SlotIndex);
}

void UInventoryComponent::SetItem(int SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::ClearItem(int SlotIndex)
{
	Items.Remove(SlotIndex);
}

const TMap<int, FInventorySlotInfo>& UInventoryComponent::GetItems()
{
	return Items;
}

int UInventoryComponent::GetItemsNum()
{
	return Items.Num();
}

