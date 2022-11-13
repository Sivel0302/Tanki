// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeekBrainsUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKI_API AGeekBrainsUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AGeekBrainsUIPlayerController(const FObjectInitializer & Obj);
    FSimpleMulticastDelegate OnMouseButtonUp;
protected:
    void SetupInputComponent() override;
    void OnLeftMouseButtonUp();

};
