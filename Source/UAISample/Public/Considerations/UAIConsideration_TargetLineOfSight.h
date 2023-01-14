// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIConsideration.h"
#include "UAIConsideration_TargetLineOfSight.generated.h"

UCLASS(ClassGroup= "PluginDevelopment", ClassGroup= "Consideration_TargetLineOfSight")
class UAISAMPLE_API UUAIConsideration_TargetLineOfSight : public UUAIConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsNeededTarget_Implementation() const override;
};
