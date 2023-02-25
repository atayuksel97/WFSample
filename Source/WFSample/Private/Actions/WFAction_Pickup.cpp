// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/WFAction_Pickup.h"
#include "WFCharacter.h"
#include "WFSampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFAction_Pickup::OnBeginPlay_Implementation()
{
	Character = Cast<AWFCharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

void UWFAction_Pickup::OnActivate_Implementation()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_Pickup::OnActivate_Implementation)
	
	if (IsValid(Character.Get()))
	{
		Character->Pickup();
		Finished();
	}
}
