﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIAction.h"
#include "UAIAction_ActorMoveToTarget.generated.h"

UCLASS(DisplayName= "Action_ActorMoveToTarget")
class UAISAMPLE_API UUAIAction_ActorMoveToTarget : public UUAIAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UUAIAction_ActorMoveToTarget();
	virtual void TickAction_Implementation(float DeltaTime) override;
	virtual void OnUpdateTargets_Implementation() override;
};
