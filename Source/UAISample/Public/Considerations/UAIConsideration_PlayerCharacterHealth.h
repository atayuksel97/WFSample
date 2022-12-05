// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIConsideration.h"
#include "UAIConsideration_PlayerCharacterHealth.generated.h"

class AUAIPlayerCharacter;

UCLASS(ClassGroup= "PluginDevelopment", DisplayName= "Consideration_PlayerCharacterHealth")
class UAISAMPLE_API UUAIConsideration_PlayerCharacterHealth : public UUAIConsideration
{
	GENERATED_BODY()
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsNeededTarget_Implementation() const override;
};
