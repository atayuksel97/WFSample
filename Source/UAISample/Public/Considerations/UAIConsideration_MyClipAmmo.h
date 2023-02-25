// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "UAIConsideration_MyClipAmmo.generated.h"

class AUAICharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "UAIConsideration_MyClipAmmo")
class UAISAMPLE_API UUAIConsideration_MyClipAmmo : public UWFConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;

	// PROPERTIES
public:
	TWeakObjectPtr<AUAICharacter> Character;
};
