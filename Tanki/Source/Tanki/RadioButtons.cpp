// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyRadioButtons.Reset();
}

void URadioButtons::HandleOnRadioChoiceChanged(ERadioChoice NewRadioChoise)
{
	if (OnRadioChoiceChanged.IsBound())
	{
		OnRadioChoiceChanged.Broadcast(NewRadioChoise);
	}
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	MyRadioButtons = SNew(SRadioButtonsList)
	.Style(&WidgetStyle)
	.OnRadioChoiceChanged(BIND_UOBJECT_DELEGATE(FOnRadioChoiceChanged, HandleOnRadioChoiceChanged));
	return MyRadioButtons.ToSharedRef();
}
