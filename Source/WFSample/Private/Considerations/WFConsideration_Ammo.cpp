// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_Ammo.h"
#include "WFCharacter.h"
#include "WFWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_Ammo::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_MyAmmo::GetValue_Implementation)

	if (bNeedTarget)
		Character = Cast<AWFCharacter>(InTargetActor);
	else
		Character = Cast<AWFCharacter>(GetControlledActor());


	if (IsValid(Character.Get()) && IsValid(Character->Weapon.Get()))
	{
		const float TotalBullets = Character->Weapon->TotalBullets;
		const float MaxBullets = Character->Weapon->MaxBullets;
		const float Value = TotalBullets / MaxBullets;
		return Value;
	}

	return 0.0f;
}
