// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/UAIAction_MoveToCover.h"
#include "AIController.h"
#include "UAISampleTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIAction_MoveToCover::OnBeginPlay_Implementation()
{
	bHasTargetActor = false;
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToCover::OnActivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToCover::TickAction_Implementation(float DeltaTime)
{
	// DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UUAIAction_MoveToCover::TickAction_Implementation"), STAT_UUAIAction_MoveToCover_TickAction_Implementation, STATGROUP_UAISample);
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIAction_MoveToCover::TickAction_Implementation)
	
	FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EnvQuery, GetControlledActor());
	HidingSpotQueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UUAIAction_MoveToCover::MoveToQueryResult);

	if (bIsQuerySuccessful)
	{
		const EPathFollowingRequestResult::Type Result = GetAIController()->MoveToLocation(TargetLocation);
		if (Result == EPathFollowingRequestResult::RequestSuccessful || EPathFollowingRequestResult::AlreadyAtGoal)
			Finished();
	}
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToCover::OnDeactivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_MoveToCover::OnUpdateTargets_Implementation()
{
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void UUAIAction_MoveToCover::MoveToQueryResult(TSharedPtr<FEnvQueryResult> Result)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIAction_MoveToCover::MoveToQueryResult)
	
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
