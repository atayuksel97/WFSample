// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/UAIConsideration_MyAmmo.h"
#include "UAICharacter.h"
#include "UAISampleTypes.h"
#include "UAIWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIConsideration_MyAmmo::OnBeginPlay_Implementation()
{
	Character = Cast<AUAICharacter>(GetPawn());
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_MyAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	UAISAMPLE_TRACE_FUNCTION()
	
	if (IsValid(Character.Get()) && IsValid(Character->Weapon.Get()))
	{
		const float TotalBullets = Character->Weapon->TotalBullets;
		const float MaxBullets = Character->Weapon->MaxBullets;
		const float Value = TotalBullets / MaxBullets;
		return Value;
	}

	return 0.0f;
}

//---------------------------------------------------------------------------------------

bool UUAIConsideration_MyAmmo::IsNeededTarget_Implementation() const
{
	return false;
}
