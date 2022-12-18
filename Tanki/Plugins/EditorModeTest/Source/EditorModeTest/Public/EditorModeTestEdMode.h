// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class FEditorModeTestEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_EditorModeTestEdModeId;
public:
	FEditorModeTestEdMode();
	virtual ~FEditorModeTestEdMode();

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	//virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void ActorSelectionChangeNotify() override;
	bool UsesToolkits() const override;
	// End of FEdMode interface

public:
    virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
    virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;
    virtual void ActorSelectionChangeNotify() override;
	
protected:
    TArray<AActor*> SelectedActors;
    void UpdateSelectedActors();
	TArray<AActor*> NPCs;
	bool FilterSelectedActors();

};
