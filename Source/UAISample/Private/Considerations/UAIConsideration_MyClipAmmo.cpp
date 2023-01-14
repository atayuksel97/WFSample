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
	Character = Cast<AUAICharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_MyClipAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIConsideration_MyClipAmmo::GetValue_Implementation)
	
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
