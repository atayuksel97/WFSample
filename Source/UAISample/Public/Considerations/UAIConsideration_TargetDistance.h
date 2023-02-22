// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIConsideration.h"
#include "UAIConsideration_TargetDistance.generated.h"

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_TargetDistance")
class UAISAMPLE_API UUAIConsideration_TargetDistance : public UUAIConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsNeededTarget_Implementation() const override;

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Consideration_TargetDistance")
	float MaxDistance;
};
