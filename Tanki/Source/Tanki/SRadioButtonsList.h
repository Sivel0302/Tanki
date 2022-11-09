// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioButtonsWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

// для чисто слейтовских виджетов можно использовать обычный C++ енам, но мы будем
// расширять этот виджет в блюпринты, поэтому сразу создаём UENUM
UENUM(BlueprintType)
enum class ERadioChoice : uint8
{
	Radio0,
	Radio1,
	Radio2,
};

DECLARE_DELEGATE_OneParam(FOnRadioChoiceChanged, ERadioChoice /*NewRadioChoise*/);

/**
 * 
 */
class TANKI_API SRadioButtonsList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRadioButtonsList)
	{}
	
	/** Called when radio choice is changed */
	SLATE_EVENT(FOnRadioChoiceChanged, OnRadioChoiceChanged)
	/** The visual style of the radio button */
	SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	ECheckBoxState IsRadioButtonChecked(ERadioChoice RadioButtonID);
	void HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, ERadioChoice RadioButtonID);
	TSharedRef<SWidget> CreateRadioButton(const FString& RadioText, ERadioChoice RadioButtonChoice);

	/** See ButtonStyle attribute */
	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);

protected:
	ERadioChoice CurrentChoice;
	FOnRadioChoiceChanged OnRadioChoiceChanged;

	/** Style resource for check boxes */
	const FCheckBoxStyle* CheckBoxStyle;
	/** Style resource for text */
	const FTextBlockStyle* TextStyle;
};
