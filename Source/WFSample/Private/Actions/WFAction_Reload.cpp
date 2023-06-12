/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/

#include "Actions/WFAction_Reload.h"
#include "WFCharacter.h"
#include "WFSampleTypes.h"
#include "WFWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFAction_Reload::OnBeginPlay_Implementation()
{
	bHasTargetActor = false;
}

//---------------------------------------------------------------------------------------

void UWFAction_Reload::OnActivate_Implementation()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_Reload::OnActivate_Implementation)
	
	const AWFCharacter* Character = Cast<AWFCharacter>(GetControlledActor());
	if (IsValid(Character) && IsValid(Character->Weapon))
		Character->Weapon->StartReloadClip();
}

//---------------------------------------------------------------------------------------

void UWFAction_Reload::TickAction_Implementation(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_Reload::TickAction_Implementation)
	
	const AWFCharacter* Character = Cast<AWFCharacter>(GetControlledActor());
	if (IsValid(Character) && IsValid(Character->Weapon) && Character->Weapon->State != EWeaponState::RELOADING)
	{
		Finished();
	}
}
