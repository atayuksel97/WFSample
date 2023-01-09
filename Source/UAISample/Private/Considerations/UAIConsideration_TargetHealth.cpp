// Fill out your copyright notice in the Description page of Project Settings.


#include "Considerations/UAIConsideration_TargetHealth.h"
#include "UAICharacter.h"
#include "UAIHealthComponent.h"
#include "UAISampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIConsideration_TargetHealth::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_TargetHealth::GetValue_Implementation(const AActor* InTargetActor)
{
	UAISAMPLE_TRACE_FUNCTION()
	
	if (IsValid(InTargetActor))
	{
		if (const AUAICharacter* Character = Cast<AUAICharacter>(InTargetActor))
			return Character->HealthComp->GetHealth() / Character->HealthComp->GetMaxHealth();
	}
	return 0.0f;
}

//---------------------------------------------------------------------------------------

bool UUAIConsideration_TargetHealth::IsNeededTarget_Implementation() const
{
	return true;
}
