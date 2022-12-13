// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowTestCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneWindowTestModule"

void FStandaloneWindowTestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StandaloneWindowTest", "Bring up StandaloneWindowTest window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
