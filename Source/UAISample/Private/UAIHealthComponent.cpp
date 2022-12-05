// Fill out your copyright notice in the Description page of Project Settings.


#include "UAIHealthComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

UUAIHealthComponent::UUAIHealthComponent() : Health{100.0f}, MaxHealth{100.0f}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUAIHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UUAIHealthComponent::TakeAnyDamage);
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIHealthComponent::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* InDamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || DamagedActor == DamageCauser)
	{
		return;
	}
		
	SetHealth(Health - Damage);

	if (Health == 0)
	{
		OnDiedEvent.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("An actor died.(Name: %s)"), *GetOwner()->GetFullName())
	}

	UE_LOG(LogTemp, Warning, TEXT("Health: %f, Damage: %f"), Health, Damage)
}
