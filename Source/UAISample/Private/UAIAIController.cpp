// Fill out your copyright notice in the Description page of Project Settings.

#include "UAIAIController.h"
#include "UAIUtilityAIComponent.h"
#include "Perception/AIPerceptionComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AUAIAIController::AUAIAIController()
{
	UtilityAIComp = CreateDefaultSubobject<UUAIUtilityAIComponent>(TEXT("UtilityAIComponent"));
	UtilityAIComp->EvaluationIntervalTime = 0.2f;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

//---------------------------------------------------------------------------------------

void AUAIAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetPawn(InPawn);
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------
