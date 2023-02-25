// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "UAIAction_ActorMoveToTarget.generated.h"

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_ActorMoveToTarget")
class UAISAMPLE_API UUAIAction_ActorMoveToTarget : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UUAIAction_ActorMoveToTarget();
	virtual void TickAction_Implementation(float DeltaTime) override;
	virtual void OnUpdateTargets_Implementation() override;
};

