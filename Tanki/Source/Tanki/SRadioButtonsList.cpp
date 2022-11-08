// Fill out your copyright notice in the Description page of Project Settings.


#include "SRadioButtonsList.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtonsList::Construct(const FArguments& InArgs)
{
	ChildSlot
    [
	    SNew(SVerticalBox)
	    + SVerticalBox::Slot()
	    [
			// first radio button
			SNew(SCheckBox)
		    [
			    SNew(STextBlock)
			    .Text(FText::FromString("Option1"))
		    ]
	    ]
	    + SVerticalBox::Slot()
	    [
		    // second radio button
		    SNew(SCheckBox)
			[
			    SNew(STextBlock)
			    .Text(FText::FromString("Option2"))
		    ]
	    ]
	    + SVerticalBox::Slot()
	    [
		    // third radio button
		    SNew(SCheckBox)
		    [
			    SNew(STextBlock)
			    .Text(FText::FromString("Option3"))
		    ]
	    ]
    ];

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
