// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UAIAction_Reload.h"
#include "UAICharacter.h"
#include "UAISampleTypes.h"
#include "UAIWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIAction_Reload::OnBeginPlay_Implementation()
{
	bHasTargetActor = false;
}

//---------------------------------------------------------------------------------------

void UUAIAction_Reload::OnActivate_Implementation()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIAction_Reload::OnActivate_Implementation)
	
	const AUAICharacter* Character = Cast<AUAICharacter>(GetControlledActor());
	if (IsValid(Character) && IsValid(Character->Weapon))
		Character->Weapon->StartReloadClip();
}

//---------------------------------------------------------------------------------------

void UUAIAction_Reload::TickAction_Implementation(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIAction_Reload::TickAction_Implementation)
	
	const AUAICharacter* Character = Cast<AUAICharacter>(GetControlledActor());
	if (IsValid(Character) && IsValid(Character->Weapon) && Character->Weapon->State != EWeaponState::RELOADING)
	{
		Finished();
	}
}
