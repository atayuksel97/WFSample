// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_MyClipAmmo.h"
#include "WFCharacter.h"
#include "WFSampleTypes.h"
#include "WFWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFConsideration_MyClipAmmo::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();
	Character = Cast<AWFCharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

float UWFConsideration_MyClipAmmo::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_MyClipAmmo::GetValue_Implementation)
	
	if (Character.IsValid() && IsValid(Character->Weapon))
	{
		return static_cast<float>(Character->Weapon->ClipBulletNum) / static_cast<float>(Character->Weapon->ClipSize);
	}

	return 0.0f;
}
