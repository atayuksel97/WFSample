/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/

#include "Considerations/WFConsideration_TargetLineOfSight.h"
#include "AIController.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_TargetLineOfSight::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_TargetLineOfSight::GetValue_Implementation)
	if (IsValid(InTargetActor) && IsValid(GetAIController()) && GetAIController()->LineOfSightTo(InTargetActor))
		return 1.0f;

	return 0.0f;
}
