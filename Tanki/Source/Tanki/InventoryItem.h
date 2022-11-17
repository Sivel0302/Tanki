// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"


UENUM()
enum class EItemType : uint8
{
	IT_Miscellaneous,
	IT_Currency,
	IT_Equipment,
	IT_Consumable
};
UENUM()
enum class EItemRarity : uint8
{
	IR_Common,
	IR_Uncommon,
	IR_Rare,
	IR_Epir,
	IR_Legendary
};
USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	// tech info
	UPROPERTY(EditAnywhere, Category = "General")
	FName ID;
	// text info
	UPROPERTY(EditAnywhere, Category = "General")
	FText Name;
	UPROPERTY(EditAnywhere, Category = "General")
	FText Description;
	// enums
	UPROPERTY(EditAnywhere, Category = "Typing")
	EItemType Type;
	UPROPERTY(EditAnywhere, Category = "Typing")
	EItemRarity Rarity;
	// visual representation
	UPROPERTY(EditAnywhere, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, Category = "Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;
	// stats
	UPROPERTY(EditAnywhere, Category = "Stats")
	int Damage;
	UPROPERTY(EditAnywhere, Category = "Stats")
	int Armor;
	UPROPERTY(EditAnywhere, Category = "Stats")
	int Intelligence;
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Id = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Count;
};


UCLASS()
class TANKI_API UInventoryItem : public UObject
{
	GENERATED_BODY()
};
