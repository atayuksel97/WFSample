/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/

#include "Actions/WFAction_MoveToTargetActor.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "AIController.h"
#include "WFSampleTypes.h"
#include "Kismet/KismetSystemLibrary.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

UWFAction_MoveToTargetActor::UWFAction_MoveToTargetActor()
	: bStopOnOverlap{true},
	  bUsePathfinding{true},
	  bCanStrafe{true},
	  bAllowPartialPaths{true},
	  bProjectDestinationToNavigation{true},
	  AcceptanceRadius{-1.0f},
	  SphereRadius{1000.0f}
{
	bShouldTick = true;
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToTargetActor::OnBeginPlay_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToTargetActor::OnActivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToTargetActor::TickAction_Implementation(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_MoveToTargetActor::TickAction_Implementation)
	
	if (IsValid(TargetActor) && IsValid(GetAIController()))
	{
		const EPathFollowingRequestResult::Type Result = GetAIController()->MoveToActor(TargetActor.Get(), AcceptanceRadius, bStopOnOverlap, bUsePathfinding, bCanStrafe,
		                                                                                NavigationQueryFilterClass, bAllowPartialPaths);
		if (Result == EPathFollowingRequestResult::Type::RequestSuccessful || Result == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		{
			Finished();
		}
	}
	else
	{
		Finished();
	}
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToTargetActor::OnDeactivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToTargetActor::OnUpdateTargets_Implementation()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_MoveToTargetActor::OnUpdateTargets_Implementation)
	
	TargetActors.Reset();
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetControlledActor()->GetActorLocation(), SphereRadius, ObjectTypesQuery, ActorClassFilter, TArray<AActor*>{GetControlledActor()}, OutActors);
	TargetActors.Append(OutActors);
}
