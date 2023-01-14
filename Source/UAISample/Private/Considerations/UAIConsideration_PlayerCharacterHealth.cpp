// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/UAIConsideration_PlayerCharacterHealth.h"
#include "UAIHealthComponent.h"
#include "UAIPlayerCharacter.h"
#include "UAISampleTypes.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UUAIConsideration_PlayerCharacterHealth::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIConsideration_PlayerCharacterHealth::GetValue_Implementation)
	
	if (const AUAIPlayerCharacter* PlayerCharacter = Cast<AUAIPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		return PlayerCharacter->HealthComp->GetHealth() / PlayerCharacter->HealthComp->GetMaxHealth();
	}

	return 0.0f;
}