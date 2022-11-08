// Fill out your copyright notice in the Description page of Project Settings.


#include "SSRadioButtons.h"
#include "SlateOptMacros.h"
#include <TraceInsights/Private/Insights/Widgets/SInsightsSettings.h>

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSRadioButtons::Construct(const FArguments& InArgs)
{
	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(0, TEXT("Option 1"))
		]
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(1, TEXT("Option 2"))
		]
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(2, TEXT("Option 3"))
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SSRadioButtons::CreateCheckbox(int32 InIndex, FString InText)
{
	return SNew(SCheckBox)
		.IsChecked_Raw(this, &SSRadioButtons::IsChecked, InIndex)
		.OnCheckStateChanged_Raw(this, &SSRadioButtons::OnCheckboxStateChanged, InIndex)
		[
			SNew(STextBlock)
			.Text(FText::FromString(InText))
		];
}

ECheckBoxState SSRadioButtons::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSRadioButtons::OnCheckboxStateChanged(ECheckBoxState NewState, int32 InIndex)
{
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
		//OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
	}
}
