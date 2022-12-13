// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowTest.h"
#include "StandaloneWindowTestStyle.h"
#include "StandaloneWindowTestCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Engine/Selection.h"

static const FName StandaloneWindowTestTabName("StandaloneWindowTest");

#define LOCTEXT_NAMESPACE "FStandaloneWindowTestModule"

void FStandaloneWindowTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneWindowTestStyle::Initialize();
	FStandaloneWindowTestStyle::ReloadTextures();

	FStandaloneWindowTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowTestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowTestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneWindowTestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowTestTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowTestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowTestTabTitle", "StandaloneWindowTest"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FLevelEditorModule& LevelEditorModule =
    FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    {
	    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	    MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After,
	    PluginCommands, FMenuExtensionDelegate::CreateRaw(this,
	    &FStandaloneWindowTestModule::AddMenuExtension));
	    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
    }
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After,
		PluginCommands, FToolBarExtensionDelegate::CreateRaw(this,
		&FStandaloneWindowTestModule::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

}

void FStandaloneWindowTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneWindowTestStyle::Shutdown();

	FStandaloneWindowTestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowTestTabName);
}

TSharedRef<SDockTab> FStandaloneWindowTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::FromString("Move selected actors");
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.OnClicked_Lambda([]()
					{
						if (GEditor)
						{
							for (FSelectionIterator Iter((GEditor->GetSelectedActorIterator())); Iter; ++Iter)
							{
								AActor* Actor = Cast<AActor>(*Iter);
								if (Actor)
								{
									Actor->AddActorLocalOffset(FVector(50.f));
								}
							}
						}
						return FReply::Handled();
					})
				[
					SNew(STextBlock)
					.Text(WidgetText)
				]
			]
		];
}

void FStandaloneWindowTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneWindowTestTabName);
}

void FStandaloneWindowTestModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FStandaloneWindowTestCommands::Get().OpenPluginWindow);
}

void FStandaloneWindowTestModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FStandaloneWindowTestCommands::Get().OpenPluginWindow);
}

void FStandaloneWindowTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneWindowTestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneWindowTestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowTestModule, StandaloneWindowTest)