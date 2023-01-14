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
	Super::OnBeginPlay_Implementation();
	Character = Cast<AUAICharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_MyAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIConsideration_MyAmmo::GetValue_Implementation)

	if (IsValid(Character.Get()) && IsValid(Character->Weapon.Get()))
	{
		const float TotalBullets = Character->Weapon->TotalBullets;
		const float MaxBullets = Character->Weapon->MaxBullets;
		const float Value = TotalBullets / MaxBullets;
		return Value;
	}

	return 0.0f;
}