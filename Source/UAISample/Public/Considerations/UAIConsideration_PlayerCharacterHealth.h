﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "UAIConsideration_PlayerCharacterHealth.generated.h"

class AUAIPlayerCharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_PlayerCharacterHealth")
class UAISAMPLE_API UUAIConsideration_PlayerCharacterHealth : public UWFConsideration
{
	GENERATED_BODY()
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
};
