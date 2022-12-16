// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorModeTestEdMode.h"
#include "EditorModeTestEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FEditorModeTestEdMode::EM_EditorModeTestEdModeId = TEXT("EM_EditorModeTestEdMode");

FEditorModeTestEdMode::FEditorModeTestEdMode()
{

}

FEditorModeTestEdMode::~FEditorModeTestEdMode()
{

}

void FEditorModeTestEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FEditorModeTestEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FEditorModeTestEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FEditorModeTestEdMode::UsesToolkits() const
{
	return true;
}




