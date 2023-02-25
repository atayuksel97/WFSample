// Fill out your copyright notice in the Description page of Project Settings.


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

//---------------------------------------------------------------------------------------

bool UWFConsideration_TargetDistance::IsNeededTarget_Implementation() const
{
	return true;
}
