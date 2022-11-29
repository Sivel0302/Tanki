// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

#include "Engine/Engine.h"


// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
    if (LocalInventoryComponent && InventoryItemsData && InventoryWidgetClass)
    {
	    ensure(InventoryWidgetClass);
	    InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
    	InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);
	    InventoryWidget->AddToViewport();
	    InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));
	    for (auto& Item : LocalInventoryComponent->GetItems())
	    {
		    FInventoryItemInfo* ItemData = GetItemData(Item.Value.ItemID);
		    if (ItemData)
		    {
			    ItemData->Icon.LoadSynchronous();
			    InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
		    }
	    }
    }

}

FInventoryItemInfo* UInventoryManagerComponent::GetItemData(FName ItemID)
{
	return InventoryItemsData ?
		InventoryItemsData->FindRow<FInventoryItemInfo>(ItemID, "") :
		nullptr;
}

void UInventoryManagerComponent::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DroppedTo)
{
	FInventorySlotInfo FromItem = DraggedFrom->GetItem();
	FInventorySlotInfo ToItem = DroppedTo->GetItem();

	DraggedFrom->Clear();
	DroppedTo->Clear();

	DroppedTo->AddItem(FromItem, *GetItemData(FromItem.ItemID));

	if (!ToItem.ItemID.IsNone())
	{
		DraggedFrom->AddItem(ToItem, *GetItemData(ToItem.ItemID));
	}
}


// Called when the game starts
void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

