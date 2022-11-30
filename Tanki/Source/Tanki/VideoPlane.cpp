// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoPlane.h"

#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "IDesktopPlatform.h"
#include "MediaSoundComponent.h"


// Sets default values
AVideoPlane::AVideoPlane()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVideoPlane::BeginPlay()
{
	Super::BeginPlay();

	/*if (MediaPlayer)
	{
		FString Path;
		TArray<FString> OutFileNames;
        IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
        if (DesktopPlatform)
        {
	        FString FileTypes = "All Files(*.PNG;*.JPG;*.MP4;*.WMV)|*.PNG;*.JPG;*.MP4;*.WMV|"
				"Image Files(*.PNG;*.JPG;)|*.PNG;*.JPG;|"
				"Video Files(*.MP4;*.WMV)|*.MP4;*.WMV";
	        uint32 SelectionFlag = 0;
	        DesktopPlatform->OpenFileDialog(FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr), "Choose content", "", "", FileTypes, SelectionFlag, OutFileNames);
	        if (OutFileNames.Num() > 0)
	        {
				Path = OutFileNames[0];
	        }
        }

		//UTexture2D * Texture = UKismetRenderingLibrary::ImportFileAsTexture2D(this, "C:\\Path\\To\\File\\name.png");
		
		//FString Path = "C:\\Users\\nikol\\Documents\\Unreal Projects\\coral_reef_adventure_1080.wmv";
		UFileMediaSource * MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = Path;
		MediaPlayer->OpenSource(MediaSource);

		UMediaSoundComponent * Comp = NewObject<UMediaSoundComponent>(this);
		Comp->SetMediaPlayer(MediaPlayer);
		Comp->RegisterComponent();
	}*/
	
}

// Called every frame
void AVideoPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVideoPlane::StartVideoTranslation()
{
	if (MediaPlayer)
	{
		FString Path;
		TArray<FString> OutFileNames;
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (DesktopPlatform)
		{
			FString FileTypes = "All Files(*.PNG;*.JPG;*.MP4;*.WMV)|*.PNG;*.JPG;*.MP4;*.WMV|"
				"Image Files(*.PNG;*.JPG;)|*.PNG;*.JPG;|"
				"Video Files(*.MP4;*.WMV)|*.MP4;*.WMV";
			uint32 SelectionFlag = 0;
			DesktopPlatform->OpenFileDialog(FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr), "Choose content", "", "", FileTypes, SelectionFlag, OutFileNames);
			if (OutFileNames.Num() > 0)
			{
				Path = OutFileNames[0];
			}
		}

		//UTexture2D * Texture = UKismetRenderingLibrary::ImportFileAsTexture2D(this, "C:\\Path\\To\\File\\name.png");
		
		//FString Path = "C:\\Users\\nikol\\Documents\\Unreal Projects\\coral_reef_adventure_1080.wmv";
		UFileMediaSource * MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = Path;
		MediaPlayer->OpenSource(MediaSource);

		UMediaSoundComponent * Comp = NewObject<UMediaSoundComponent>(this);
		Comp->SetMediaPlayer(MediaPlayer);
		Comp->RegisterComponent();
	}
}

