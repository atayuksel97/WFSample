﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Considerations/UAIConsideration_TargetDistance.h"

#include "AIController.h"
#include "UAISampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIConsideration_TargetDistance::OnBeginPlay_Implementation()
{
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_TargetDistance::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIConsideration_TargetDistance::GetValue_Implementation)
	
	if (IsValid(InTargetActor) && IsValid(GetControlledActor()))
	{
		return GetControlledActor()->GetDistanceTo(InTargetActor) / MaxDistance;
	}
	return 0.0f;
}

//---------------------------------------------------------------------------------------

bool UUAIConsideration_TargetDistance::IsNeededTarget_Implementation() const
{
	return true;
}
