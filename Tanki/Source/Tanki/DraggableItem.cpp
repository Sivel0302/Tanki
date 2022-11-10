// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItem.h"

void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (NameText)
	{
		NameText->SetText(FruitName);
	}
}
