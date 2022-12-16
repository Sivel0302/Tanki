// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorModeTest.h"
#include "EditorModeTestEdMode.h"

#define LOCTEXT_NAMESPACE "FEditorModeTestModule"

void FEditorModeTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FEditorModeTestEdMode>(FEditorModeTestEdMode::EM_EditorModeTestEdModeId, LOCTEXT("EditorModeTestEdModeName", "EditorModeTestEdMode"), FSlateIcon(), true);
}

void FEditorModeTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FEditorModeTestEdMode::EM_EditorModeTestEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorModeTestModule, EditorModeTest)