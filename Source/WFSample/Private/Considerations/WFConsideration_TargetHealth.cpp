// Fill out your copyright notice in the Description page of Project Settings.


#include "Considerations/WFConsideration_TargetHealth.h"
#include "WFCharacter.h"
#include "WFHealthComponent.h"
#include "WFSampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_TargetHealth::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_TargetHealth::GetValue_Implementation)
	
	if (IsValid(InTargetActor))
	{
		if (const AWFCharacter* Character = Cast<AWFCharacter>(InTargetActor))
			return Character->HealthComp->GetHealth() / Character->HealthComp->GetMaxHealth();
	}
	return 0.0f;
}

//---------------------------------------------------------------------------------------

bool UWFConsideration_TargetHealth::IsTargetNeeded_Implementation() const
{
	return true;
}
