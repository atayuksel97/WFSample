﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "WFConsideration_TargetDistance.generated.h"

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_TargetDistance")
class WFSAMPLE_API UWFConsideration_TargetDistance : public UWFConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Consideration_TargetDistance")
	float MaxDistance;
};
