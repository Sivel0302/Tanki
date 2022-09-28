// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include <Components/ActorComponent.h>


void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float takedDamageValue = DamageData.DamageValue;
	CurrentHealth -= takedDamageValue;
	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
	else
	{
		if (OnHealthChanged.IsBound())
		{
			OnHealthChanged.Broadcast(takedDamageValue);
		}
	}

}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

void UHealthComponent::AddHealth(float newHealth)
{
	CurrentHealth += newHealth;
	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

float UHealthComponent::GetHealthState()
{
	return CurrentHealth / MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}



