// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "RadioButtonsWidgetStyle.h"
#include <Templates/SharedPointer.h>
#include <TraceInsights/Private/Insights/Widgets/SInsightsSettings.h>

#include "RadioButtonsWidgetStyle.h"

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32)

class TANKI_API SSRadioButtons : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSRadioButtons)
	{}

	SLATE_ATTRIBUTE(int32, Count);
	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged);
	
	/** The visual style of the radio button */
	SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FOnRadioButtonChanged OnRadioButtonChanged;

	/** See ButtonStyle attribute */
	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);

private:
	TSharedRef<SWidget> CreateCheckbox(int32 InIndex, FString InText);

	int32 CurrentIndex = 0;

	ECheckBoxState IsChecked(int32 InIndex) const;

	void OnCheckboxStateChanged(ECheckBoxState NewState, int32 InIndex);

	/** Style resource for check boxes */
	const FCheckBoxStyle* CheckBoxStyle;
	/** Style resource for text */
	const FTextBlockStyle* TextStyle;


};
