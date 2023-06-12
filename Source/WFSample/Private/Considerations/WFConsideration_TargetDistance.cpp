/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/


#include "Considerations/WFConsideration_TargetDistance.h"

#include "AIController.h"
#include "WFSampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_TargetDistance::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_TargetDistance::GetValue_Implementation)
	
	if (IsValid(InTargetActor) && IsValid(GetControlledActor()))
	{
		return GetControlledActor()->GetDistanceTo(InTargetActor) / MaxDistance;
	}
	return 0.0f;
}
