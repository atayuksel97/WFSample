// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/UAIConsideration_MyClipAmmo.h"
#include "UAICharacter.h"
#include "UAISampleTypes.h"
#include "UAIWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIConsideration_MyClipAmmo::OnBeginPlay_Implementation()
{
	Character = Cast<AUAICharacter>(GetPawn());
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_MyClipAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	UAISAMPLE_TRACE_FUNCTION()
	
	if (Character.IsValid() && IsValid(Character->Weapon))
	{
		return static_cast<float>(Character->Weapon->ClipBulletNum) / static_cast<float>(Character->Weapon->ClipSize);
	}

	return 0.0f;
}

//---------------------------------------------------------------------------------------

bool UUAIConsideration_MyClipAmmo::IsNeededTarget_Implementation() const
{
	return false;
}
