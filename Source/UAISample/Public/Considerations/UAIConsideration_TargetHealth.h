// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIConsideration.h"
#include "UAIConsideration_TargetHealth.generated.h"

class UUAIHealthComponent;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_TargetHealth")
class UAISAMPLE_API UUAIConsideration_TargetHealth : public UUAIConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsNeededTarget_Implementation() const override;
};
