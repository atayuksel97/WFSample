/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "WFAction_ActorMoveToTarget.generated.h"

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_ActorMoveToTarget")
class WFSAMPLE_API UWFAction_ActorMoveToTarget : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UWFAction_ActorMoveToTarget();
	virtual void TickAction_Implementation(float DeltaTime) override;
	virtual void OnUpdateTargets_Implementation() override;
};

