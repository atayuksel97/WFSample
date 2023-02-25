// Fill out your copyright notice in the Description page of Project Settings.

#include "WFAIController.h"
#include "WFBrainComponent.h"
#include "Perception/AIPerceptionComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AWFAIController::AWFAIController()
{
	WFBrainComponent = CreateDefaultSubobject<UWFBrainComponent>(TEXT("BrainComponent"));
	WFBrainComponent->EvaluationIntervalTime = 0.2f;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

//---------------------------------------------------------------------------------------

void AWFAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetPawn(InPawn);
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------
