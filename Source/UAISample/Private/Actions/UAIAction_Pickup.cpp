// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/UAIAction_Pickup.h"
#include "UAICharacter.h"
#include "UAISampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIAction_Pickup::OnBeginPlay_Implementation()
{
	Character = Cast<AUAICharacter>(GetPawn());
}

//---------------------------------------------------------------------------------------

void UUAIAction_Pickup::OnActivate_Implementation()
{
	UAISAMPLE_TRACE_FUNCTION()
	
	if (IsValid(Character.Get()))
	{
		Character->Pickup();
		Finished();
	}
}
