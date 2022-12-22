// Fill out your copyright notice in the Description page of Project Settings.


#include "SavingsManager.h"

#include "Kismet/GameplayStatics.h"

void USavingsManager::Init()
{
	CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));

	ExistingSavedSlots.Empty();
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString FilePath = FPaths::Combine(FPaths::ProjectContentDir(), ExistingSavedSlotsFilePath);
	if (PlatformFile.FileExists(*FilePath))
	{
		FString ExistingSavingsArray;
		if (FFileHelper::LoadFileToString(ExistingSavingsArray, *FilePath))
		{
			ExistingSavingsArray.ParseIntoArray(ExistingSavedSlots, TEXT(","));
		}
	}

	/*FString ProjectDirectory = FPaths::ProjectDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectDirectory: %s"), *ProjectDirectory);

	FString ProjectConfigDirectory = FPaths::ProjectConfigDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectConfigDir: %s"), *ProjectConfigDirectory);
	
	FString ProjectContentDirectory = FPaths::ProjectContentDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectContentDir: %s"), *ProjectContentDirectory);
	
	FString ProjectIntermediateDirectory = FPaths::ProjectIntermediateDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectIntermediateDirectory: %s"), *ProjectIntermediateDirectory);
	
	FString ProjectLogDirectory = FPaths::ProjectLogDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectLogDir: %s"), *ProjectLogDirectory);
	
	FString ProjectModsDirectory = FPaths::ProjectModsDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectModsDir: %s"), *ProjectModsDirectory);
	
	FString ProjectPluginsDirectory = FPaths::ProjectPluginsDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectPluginsDir: %s"), *ProjectPluginsDirectory);
	
	FString ProjectSavedDirectory = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *ProjectSavedDirectory);
	
	FString ProjectUserDirectory = FPaths::ProjectUserDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectUserDir: %s"), *ProjectUserDirectory);
	
	FString ProjectPersistentDownloadDirectory = FPaths::ProjectPersistentDownloadDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectPersistentDownloadDir: %s"), *ProjectPersistentDownloadDirectory);
	
	FString ProjectPlatformExtensionsDirectory = FPaths::ProjectPlatformExtensionsDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectPlatformExtensionsDir: %s"), *ProjectPlatformExtensionsDirectory);*/

	//создание директории
	/*FString MyDirectory1 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/Some";
	IPlatformFile& FileManager1 = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager1.CreateDirectory(*MyDirectory1))
	{
		UE_LOG(LogTemp, Warning, TEXT("DirectoryCreate: Directory was created"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DirectoryCreate: Directory was not created"));
	}*/

	//проверка существования директории
	/*FString MyDirectory = "C:/Users/nikol/Documents/Unreal Projects/Tanki/Some/test";
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager.DirectoryExists(*MyDirectory))
	{
		UE_LOG(LogTemp, Warning, TEXT("DirectoryExist: Directory Exists"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DirectoryExist: Directory Does not exist"));
	}*/

	//удаление директории
	/*FString MyDirectory2 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/Some/test";
    IPlatformFile& FileManager2 = FPlatformFileManager::Get().GetPlatformFile();
    if (FileManager2.DeleteDirectory(*MyDirectory2))
    {
		UE_LOG(LogTemp, Warning, TEXT("DirectoryDelete: Directory was deleted"));
    }
    else
    {
		UE_LOG(LogTemp, Warning, TEXT("DirectoryDelete: Directory was not deleted"));
    }*/

	//проверка существования файла
	/*FString MyFile = "C:/Users/nikol/Documents/Unreal Projects/Tanki/File.txt";
    IPlatformFile& FileManager3 = FPlatformFileManager::Get().GetPlatformFile();
    if (FileManager3.FileExists(*MyFile))
    {
		UE_LOG(LogTemp, Warning, TEXT("FileExist: File found!"));
    }
    else
    {
		UE_LOG(LogTemp, Warning, TEXT("FileExist: File not found!"));
    }*/

	//копирование файла
	/*FString MyFile1 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/File.txt";
	FString MyFileDest = "C:/Users/nikol/Documents/Unreal Projects/Tanki/File1.txt";
	IPlatformFile& FileManager4 = FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Dest: %s"), *MyFileDest);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Source: %s"), *MyFile1);
	if (FileManager4.CopyFile(*MyFileDest, *MyFile1, EPlatformFileRead::None, EPlatformFileWrite::None))
	{
		UE_LOG(LogTemp, Warning, TEXT("FileCopy: File copied!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileCopy: File not copied!"));
	}*/

	//перемещение файла
	/*FString MyFile2 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/File.txt";
	FString MyFileDest1 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/test/File.txt";
	IPlatformFile& FileManager5 = FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Dest: %s"), *MyFileDest1);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Source: %s"), *MyFile2);
	if (FileManager5.MoveFile(*MyFileDest1, *MyFile2))
	{
		UE_LOG(LogTemp, Warning, TEXT("FileMove: File moved!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileMove: File not moved!"));
	}*/

	//удаление файла
	/*FString MyFile3 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/File1.txt";
	IPlatformFile& FileManager6 = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager6.DeleteFile(*MyFile3))
	{
		UE_LOG(LogTemp, Warning, TEXT("FileDelete: File deleted!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileDelete: File not deleted!"));
	}*/

	//получение размера файла
	/*FString MyFile4 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/test/File.txt";
	IPlatformFile& FileManager7 = FPlatformFileManager::Get().GetPlatformFile();
	int FileSize = FileManager7.FileSize(*MyFile4);
	if (FileSize > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("FileSize: File Size: %d"), FileSize);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileSize: File not found!"));
	}*/

	//запись в бинарный файл
	/*int32 MyInteger = 10;
	FString MyFile5 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/test/File.txt";
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* FileHandle = PlatformFile.OpenWrite(*MyFile5);
	if (FileHandle)
	{
		int32* IntPointer = &MyInteger;
		uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);
		if (FileHandle->Write(ByteBuffer, sizeof(int32)))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileWrite: Sucsessful write!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileWrite: NOT sucsessful write("));
		}
		delete FileHandle;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileWrite: NOT sucsessful write("));
	}*/

	//чтение бинарного файла
	/*int32 MyInteger1;
	FString MyFile6 = "C:/Users/nikol/Documents/Unreal Projects/Tanki/test/File.txt";
	IPlatformFile& PlatformFile1 = FPlatformFileManager::Get().GetPlatformFile();
    IFileHandle* FileHandle1 = PlatformFile1.OpenRead(*MyFile6);
    if (FileHandle1)
    {
	    int32* IntPointer = &MyInteger1;
	    uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);
	    FileHandle1->Read(ByteBuffer, sizeof(int32));
	    //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Read integer is %d"), MyInteger));
    	UE_LOG(LogTemp, Warning, TEXT("Read integer is %d"), MyInteger1);
	    delete FileHandle1;
    }*/

	//запись строки в файл
	/*FString MyDir = "C:/Users/nikol/Documents/Unreal Projects/Tanki/test/test2";
    FString MyFile7 = FString("File.txt");
    FString TextToSave = FString("Lorem ipsum");
    bool AllowOverwriting = true;
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (PlatformFile.CreateDirectoryTree(*MyDir))
    {
	    FString AbsoluteFilePath = MyDir + "/" + MyFile7;
	    if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
	    {
			FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath);
	    }
    }*/

	//чтение строки из файла
	/*FString MyFile8 = FString("C:/Users/nikol/Documents/Unreal Projects/Tanki/test/test2/File.txt");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*MyFile8))
	{
		FString LoadedText;
		if (FFileHelper::LoadFileToString(LoadedText, *MyFile8))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, LoadedText);
			//UE_LOG(LogTemp, Warning, TEXT("Read string is %s"), LoadedText); не выводит FString!!
		}
	}*/



}

bool USavingsManager::DoesSaveGameExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void USavingsManager::LoadGame(const FString& SlotName)
{
	//CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0,
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &USavingsManager::OnGameLoadedFromSlotHandle));
}

void USavingsManager::SaveCurrentGame(const FString& SlotName)
{
	//UGameplayStatics::SaveGameToSlot(CurrentGameObject, SlotName, 0);

	UGameplayStatics::AsyncSaveGameToSlot(CurrentGameObject, SlotName, 0,
		FAsyncSaveGameToSlotDelegate::CreateUObject(this, &USavingsManager::OnGameSavedToSlotHandle));

}

const TArray<FString>& USavingsManager::GetExistingSavedSlots() const
{
	return ExistingSavedSlots;
}

void USavingsManager::OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentGameObject = Cast<UTestSaveGame>(SaveGame);
    if (OnGameLoadedFromSlot.IsBound())
    {
		OnGameLoadedFromSlot.Broadcast(SlotName);
    }

}

void USavingsManager::OnGameSavedToSlotHandle(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (OnGameSavedToSlot.IsBound())
	{
		OnGameSavedToSlot.Broadcast(SlotName);
	}
	if (!ExistingSavedSlots.Contains(SlotName))
	{
		ExistingSavedSlots.Add(SlotName);
		CacheExistingSavedSlotsInfo();
	}
}

void USavingsManager::CacheExistingSavedSlotsInfo()
{
	FString FilePath = FPaths::Combine(FPaths::ProjectContentDir(), ExistingSavedSlotsFilePath);
    FString ExistingSavingsArray = "";
    for (const FString& Slot : ExistingSavedSlots)
    {
		ExistingSavingsArray += Slot + ",";
    }
    FFileHelper::SaveStringToFile(ExistingSavingsArray, *FilePath, FFileHelper::EEncodingOptions::ForceUnicode, &IFileManager::Get(), FILEWRITE_EvenIfReadOnly);

}
