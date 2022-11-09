// Fill out your copyright notice in the Description page of Project Settings.


#include "SRadioButtonsList.h"
#include "SlateOptMacros.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtonsList::Construct(const FArguments& InArgs)
{
	SetRadioButtonStyle(InArgs._Style);
	OnRadioChoiceChanged = InArgs._OnRadioChoiceChanged;
	ChildSlot
    [
	    SNew(SVerticalBox)
	    + SVerticalBox::Slot()
	    [
			// first radio button
			CreateRadioButton("Option1", ERadioChoice::Radio0)
	    ]
	    + SVerticalBox::Slot()
	    [
		    // second radio button
			CreateRadioButton("Option2", ERadioChoice::Radio1)
	    ]
	    + SVerticalBox::Slot()
	    [
		    // third radio button
			CreateRadioButton("Option3", ERadioChoice::Radio2)
	    ]
    ];

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

ECheckBoxState SRadioButtonsList::IsRadioButtonChecked(ERadioChoice RadioButtonID)
{
    return (CurrentChoice == RadioButtonID)
		? ECheckBoxState::Checked
		: ECheckBoxState::Unchecked;
}

void SRadioButtonsList::HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, ERadioChoice RadioButtonID)
{
    if (NewRadioState == ECheckBoxState::Checked)
    {
        CurrentChoice = RadioButtonID;
    	OnRadioChoiceChanged.ExecuteIfBound(CurrentChoice);
    }
}

TSharedRef<SWidget> SRadioButtonsList::CreateRadioButton(const FString& RadioText, ERadioChoice RadioButtonChoice)
{
	return SNew(SCheckBox)
		.IsChecked(MakeAttributeRaw(this, &SRadioButtonsList::IsRadioButtonChecked, RadioButtonChoice))
		.OnCheckStateChanged(this, &SRadioButtonsList::HandleRadioButtonStateChanged, RadioButtonChoice)
		.Style(CheckBoxStyle)
		[
			SNew(STextBlock)
			.Text(FText::FromString(RadioText))
			.TextStyle(TextStyle)
		];

}

void SRadioButtonsList::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
{
	CheckBoxStyle = &InStyle->CheckBoxStyle;
    TextStyle = &InStyle->TextStyle;
}


