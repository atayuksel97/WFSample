// Fill out your copyright notice in the Description page of Project Settings.

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

//---------------------------------------------------------------------------------------

bool UWFConsideration_TargetLineOfSight::IsTargetNeeded_Implementation() const
{
	return true;
}
