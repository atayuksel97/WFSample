/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/


#include "WFHealthComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

UWFHealthComponent::UWFHealthComponent() : Health{100.0f}, MaxHealth{100.0f}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWFHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UWFHealthComponent::TakeAnyDamage);
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFHealthComponent::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* InDamageType, AController* InstigatedBy, AActor* DamageCauser)
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
