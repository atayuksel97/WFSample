// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_MyHealth.h"
#include "WFCharacter.h"
#include "WFHealthComponent.h"
#include "WFSampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFConsideration_MyHealth::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();
	const AWFCharacter* Character = Cast<AWFCharacter>(GetControlledActor());
	HealthComp = Character ? Cast<AWFCharacter>(GetControlledActor())->HealthComp : nullptr;
}

//---------------------------------------------------------------------------------------

float UWFConsideration_MyHealth::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_MyHealth::GetValue_Implementation)

	if (HealthComp.IsValid())
	{
		return HealthComp->GetHealth() / HealthComp->GetMaxHealth();
	}

	return 0.0f;
}

//---------------------------------------------------------------------------------------

#if ENABLE_VISUAL_LOG
void UWFConsideration_MyHealth::GrabDebugSnapshot(FVisualLogEntry* Snapshot) const
{
	Super::GrabDebugSnapshot(Snapshot);

	if (IsValid(HealthComp.Get()))
		GetVisualLogCategory()->Add(TEXT("Health"), FString::Printf(TEXT("%f"), HealthComp->GetHealth()));
}
#endif
