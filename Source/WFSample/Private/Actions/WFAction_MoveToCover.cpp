/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/


#include "Actions/WFAction_MoveToCover.h"
#include "AIController.h"
#include "WFSampleTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFAction_MoveToCover::OnBeginPlay_Implementation()
{
	bHasTargetActor = false;
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToCover::OnActivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToCover::TickAction_Implementation(float DeltaTime)
{
	// DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UWFAction_MoveToCover::TickAction_Implementation"), STAT_UWFAction_MoveToCover_TickAction_Implementation, STATGROUP_WFSample);
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_MoveToCover::TickAction_Implementation)

	FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EnvQuery, GetControlledActor());
	HidingSpotQueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UWFAction_MoveToCover::MoveToQueryResult);

	if (bIsQuerySuccessful)
	{
		const EPathFollowingRequestResult::Type Result = GetAIController()->MoveToLocation(TargetLocation);
		if (Result == EPathFollowingRequestResult::RequestSuccessful || EPathFollowingRequestResult::AlreadyAtGoal)
			Finished();
	}
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToCover::OnDeactivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_MoveToCover::OnUpdateTargets_Implementation()
{
}

//---------------------------------------------------------------------------------------

#if ENABLE_VISUAL_LOG
void UWFAction_MoveToCover::GrabDebugSnapshot(FVisualLogEntry* Snapshot) const
{
	Super::GrabDebugSnapshot(Snapshot);

	GetVisualLogCategory()->Add(TEXT("bIsQuerySuccessful"), bIsQuerySuccessful ? TEXT("true") : TEXT("false"));
}
#endif


//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void UWFAction_MoveToCover::MoveToQueryResult(TSharedPtr<FEnvQueryResult> Result)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_MoveToCover::MoveToQueryResult)

	if (Result->IsSuccessful())
	{
		bIsQuerySuccessful = true;
		TargetLocation = Result->GetItemAsLocation(0);
	}
	else
	{
		bIsQuerySuccessful = false;
	}
}
