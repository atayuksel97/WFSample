// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_Health.h"
#include "WFCharacter.h"
#include "WFHealthComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_Health::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_MyHealth::GetValue_Implementation)
	
	if (bNeedTarget)
		Character = Cast<AWFCharacter>(InTargetActor);
	else
		Character = Cast<AWFCharacter>(GetControlledActor());

	if (IsValid(Character))
	{
		return Character->HealthComp->GetHealth() / Character->HealthComp->GetMaxHealth();
	}

	return 0.0f;
}

//---------------------------------------------------------------------------------------

#if ENABLE_VISUAL_LOG
void UWFConsideration_Health::GrabDebugSnapshot(FVisualLogEntry* Snapshot) const
{
	Super::GrabDebugSnapshot(Snapshot);

	if (IsValid(Character))
		GetVisualLogCategory()->Add(TEXT("Health"), FString::Printf(TEXT("%f"), Character->HealthComp->GetHealth()));
}
#endif
