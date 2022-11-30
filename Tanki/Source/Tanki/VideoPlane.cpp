// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoPlane.h"

#include "FileMediaSource.h"
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

	if (MediaPlayer)
	{
		FString Path = "C:\\Users\\nikol\\Documents\\Unreal Projects\\coral_reef_adventure_1080.wmv";
		UFileMediaSource * MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = Path;
		MediaPlayer->OpenSource(MediaSource);

		UMediaSoundComponent * Comp = NewObject<UMediaSoundComponent>(this);
		Comp->SetMediaPlayer(MediaPlayer);
		Comp->RegisterComponent();
	}
	
}

// Called every frame
void AVideoPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

