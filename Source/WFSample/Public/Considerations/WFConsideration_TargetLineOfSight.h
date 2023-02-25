// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "WFConsideration_TargetLineOfSight.generated.h"

UCLASS(ClassGroup= "WiseFelineSample", ClassGroup= "Consideration_TargetLineOfSight")
class WFSAMPLE_API UWFConsideration_TargetLineOfSight : public UWFConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsNeededTarget_Implementation() const override;
};
