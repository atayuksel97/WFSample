/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/


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
