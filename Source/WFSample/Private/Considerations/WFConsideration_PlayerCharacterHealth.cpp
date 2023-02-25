// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/WFConsideration_PlayerCharacterHealth.h"
#include "WFHealthComponent.h"
#include "WFPlayerCharacter.h"
#include "WFSampleTypes.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

float UWFConsideration_PlayerCharacterHealth::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_PlayerCharacterHealth::GetValue_Implementation)
	
	if (const AWFPlayerCharacter* PlayerCharacter = Cast<AWFPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		return PlayerCharacter->HealthComp->GetHealth() / PlayerCharacter->HealthComp->GetMaxHealth();
	}

	return 0.0f;
}