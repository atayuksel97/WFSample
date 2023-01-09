// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UAIAction_MoveToTargetActor.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "AIController.h"
#include "UAISampleTypes.h"
#include "Kismet/KismetSystemLibrary.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

UUAIAction_MoveToTargetActor::UUAIAction_MoveToTargetActor()
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

void UUAIAction_MoveToTargetActor::OnBeginPlay_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToTargetActor::OnActivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToTargetActor::TickAction_Implementation(float DeltaTime)
{
	UAISAMPLE_TRACE_FUNCTION()
	
	if (IsValid(TargetActor))
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

void UUAIAction_MoveToTargetActor::OnDeactivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToTargetActor::OnUpdateTargets_Implementation()
{
	UAISAMPLE_TRACE_FUNCTION()
	
	TargetActors.Reset();
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetPawn()->GetActorLocation(), SphereRadius, ObjectTypesQuery, ActorClassFilter, TArray<AActor*>{GetPawn()}, OutActors);
	TargetActors.Append(OutActors);
}
