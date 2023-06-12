/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#include "Considerations/WFConsideration_OverlappingPickup.h"
#include "WFCharacter.h"
#include "WFPickup.h"
#include "WFSampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFConsideration_OverlappingPickup::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();
	Character = Cast<AWFCharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

float UWFConsideration_OverlappingPickup::GetValue_Implementation(const AActor* InTargetActor)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFConsideration_OverlappingPickup::GetValue_Implementation)
	
	if (IsValid(Character.Get()) && IsValid(Character->OverlappedPickup.Get()))
		return 1.0f;

	return 0.0f;
}
