// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_ClipAmmo.h"
#include "WFCharacter.h"
#include "WFSampleTypes.h"
#include "WFWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_ClipAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_MyClipAmmo::GetValue_Implementation)
	
	if (bNeedTarget)
		Character = Cast<AWFCharacter>(InTargetActor);
	else
		Character = Cast<AWFCharacter>(GetControlledActor());
	
	if (IsValid(Character.Get()) && IsValid(Character->Weapon))
	{
		return static_cast<float>(Character->Weapon->ClipBulletNum) / static_cast<float>(Character->Weapon->ClipSize);
	}

	return 0.0f;
}
