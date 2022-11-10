// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItem.h"

#include "FruitDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/VerticalBox.h"

void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (NameText)
	{
		NameText->SetText(FruitName);
	}
}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UFruitDragDropOperation::StaticClass());
    if (OutOperation)
    {
	    UFruitDragDropOperation* FruitDragDropOperation = Cast<UFruitDragDropOperation>(OutOperation);
	    FruitDragDropOperation->FruitName = FruitName;
	    FruitDragDropOperation->DefaultDragVisual = this;
	    SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.7f));
	    SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	    FruitDragDropOperation->OnDragCancelled.AddDynamic(this, &UDraggableItem::OnDragCancelledHandle);
    }
    else
    {
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    }

}

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	auto verticalBox = Cast<UVerticalBox>(GetParent());
	UFruitDragDropOperation* FruitDragDropOperation = Cast<UFruitDragDropOperation>(InOperation);
	if (FruitDragDropOperation && verticalBox && this != FruitDragDropOperation->DefaultDragVisual)
	{
		int32 IndexDragged = verticalBox->GetChildIndex(FruitDragDropOperation->DefaultDragVisual);
		if (IndexDragged != -1)
		{
			verticalBox->RemoveChildAt(IndexDragged);
			TArray<UWidget*> VBChildren = verticalBox->GetAllChildren();
			verticalBox->ClearChildren();
			for (int32 Counter = 0; Counter < VBChildren.Num(); Counter++)
			{
				verticalBox->AddChildToVerticalBox(VBChildren[Counter]);
				if (VBChildren[Counter] == this)
				{
					verticalBox->AddChildToVerticalBox(FruitDragDropOperation->DefaultDragVisual);
				}
			}
		}
	}
	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual)
	{
		Cast<UUserWidget>(InOperation->DefaultDragVisual)->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		InOperation->DefaultDragVisual->SetVisibility(ESlateVisibility::Visible);
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDraggableItem::OnDragCancelledHandle(UDragDropOperation* Operation)
{
	SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
    SetVisibility(ESlateVisibility::Visible);
}
