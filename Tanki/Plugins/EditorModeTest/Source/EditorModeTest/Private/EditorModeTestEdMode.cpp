// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorModeTestEdMode.h"
#include "EditorModeTestEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "Engine/Selection.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSystem/InteractableActor.h"
#include "QuestSystem/QuestSystemCharacter.h"

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

	UpdateSelectedActors();
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

void FEditorModeTestEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (AActor* BoundedActor : NPCs)
	{
		DrawWireBox(
			PDI,
			BoundedActor->GetComponentsBoundingBox(true),
			FColor::Yellow,
			1);
	}
	FEdMode::Render(View, Viewport, PDI);
}

void FEditorModeTestEdMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View,
	FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	for (AActor* SelectedActor : NPCs)
	{
		if (Canvas)
		{
			FBox Bounds = SelectedActor->GetComponentsBoundingBox(true);
			FVector drawPos = Bounds.GetCenter() +
				FVector(0.f, 0.f, Bounds.GetExtent().Z);
			FVector2D PixelLocation;
			View->ScreenToPixel(View->WorldToScreen(drawPos), PixelLocation);
			PixelLocation /= ViewportClient->GetDPIScale();
			UFont* RenderFont = GEngine->GetSmallFont();
			Canvas->DrawShadowedText(PixelLocation.X, PixelLocation.Y,
				FText::FromString(SelectedActor->GetName()),
			RenderFont, FColor::Yellow);
		}
	}
}

void FEditorModeTestEdMode::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors();
}

void FEditorModeTestEdMode::UpdateSelectedActors()
{
	SelectedActors.Empty();
	USelection* ActorsSelection = GEditor->GetSelectedActors();
	for (FSelectionIterator Iter(*ActorsSelection); Iter; ++Iter)
	{
		AActor* LevelActor = Cast<AActor>(*Iter);
		if (LevelActor && !SelectedActors.Contains(LevelActor))
		{
			SelectedActors.Add(LevelActor);
		}
	}

	NPCs.Empty();
	if (!FilterSelectedActors())
	{
		UGameplayStatics::GetAllActorsOfClass(GEditor->GetWorld(), AQuestSystemCharacter::StaticClass(), NPCs);
	}
}

bool FEditorModeTestEdMode::FilterSelectedActors()
{
	bool NPCExist = false;
	for (auto SelectedActor : SelectedActors)
	{
		AQuestSystemCharacter* QuestSystemCharacter = Cast<AQuestSystemCharacter>(SelectedActor);
		if (QuestSystemCharacter)
		{
			NPCExist = true;
		}
	}
	if (NPCExist)
	{
		return true;
	}
	else
	{
		return false;
	}
}




