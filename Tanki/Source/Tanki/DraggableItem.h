// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DraggableItem.generated.h"

/**
 * 
 */
UCLASS()
class TANKI_API UDraggableItem : public UUserWidget
{
	GENERATED_BODY()

public:
    void NativePreConstruct() override;
    UPROPERTY(EditAnywhere)
    FText FruitName;
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock * NameText;

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UFUNCTION()
	void OnDragCancelledHandle(UDragDropOperation* Operation);

};
