/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

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
