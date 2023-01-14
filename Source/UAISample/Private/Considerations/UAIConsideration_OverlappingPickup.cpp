// Fill out your copyright notice in the Description page of Project Settings.

#include "Considerations/UAIConsideration_OverlappingPickup.h"
#include "UAICharacter.h"
#include "UAIPickup.h"
#include "UAISampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIConsideration_OverlappingPickup::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();
	Character = Cast<AUAICharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

float UUAIConsideration_OverlappingPickup::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIConsideration_OverlappingPickup::GetValue_Implementation)
	
	if (IsValid(Character.Get()) && IsValid(Character->OverlappedPickup.Get()))
		return 1.0f;

	return 0.0f;
}
