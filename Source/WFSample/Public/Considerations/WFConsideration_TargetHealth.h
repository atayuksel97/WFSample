// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "WFConsideration_TargetHealth.generated.h"

class UWFHealthComponent;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_TargetHealth")
class WFSAMPLE_API UWFConsideration_TargetHealth : public UWFConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsTargetNeeded_Implementation() const override;
};
