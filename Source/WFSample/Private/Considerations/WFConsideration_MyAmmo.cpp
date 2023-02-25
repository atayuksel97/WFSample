// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_MyAmmo.h"
#include "WFCharacter.h"
#include "WFSampleTypes.h"
#include "WFWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFConsideration_MyAmmo::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();
	Character = Cast<AWFCharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

float UWFConsideration_MyAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_MyAmmo::GetValue_Implementation)

	if (IsValid(Character.Get()) && IsValid(Character->Weapon.Get()))
	{
		const float TotalBullets = Character->Weapon->TotalBullets;
		const float MaxBullets = Character->Weapon->MaxBullets;
		const float Value = TotalBullets / MaxBullets;
		return Value;
	}

	return 0.0f;
}