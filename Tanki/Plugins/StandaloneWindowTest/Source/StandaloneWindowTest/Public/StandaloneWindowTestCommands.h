// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StandaloneWindowTestStyle.h"

class FStandaloneWindowTestCommands : public TCommands<FStandaloneWindowTestCommands>
{
public:

	FStandaloneWindowTestCommands()
		: TCommands<FStandaloneWindowTestCommands>(TEXT("StandaloneWindowTest"), NSLOCTEXT("Contexts", "StandaloneWindowTest", "StandaloneWindowTest Plugin"), NAME_None, FStandaloneWindowTestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};