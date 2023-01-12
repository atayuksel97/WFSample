﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/UAIConsideration_MyHealth.h"
#include "UAICharacter.h"
#include "UAIHealthComponent.h"
#include "UAISampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIConsideration_MyHealth::OnBeginPlay_Implementation()
{
	HealthComp = Cast<AUAICharacter>(GetPawn())->HealthComp;
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_MyHealth::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIConsideration_MyHealth::GetValue_Implementation)
	
	if (HealthComp.IsValid())
	{
		return HealthComp->GetHealth() / HealthComp->GetMaxHealth();
	}

	return 0.0f;
}

//---------------------------------------------------------------------------------------

bool UUAIConsideration_MyHealth::IsNeededTarget_Implementation() const
{
	return false;
}
