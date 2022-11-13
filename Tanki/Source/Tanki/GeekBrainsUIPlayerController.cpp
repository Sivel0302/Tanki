// Fill out your copyright notice in the Description page of Project Settings.


#include "GeekBrainsUIPlayerController.h"

AGeekBrainsUIPlayerController::AGeekBrainsUIPlayerController(const FObjectInitializer& Obj) : Super(Obj)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void AGeekBrainsUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
    {
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AGeekBrainsUIPlayerController::OnLeftMouseButtonUp);
    }

}

void AGeekBrainsUIPlayerController::OnLeftMouseButtonUp()
{
	if (OnMouseButtonUp.IsBound())
	{
		OnMouseButtonUp.Broadcast();
	}
}
