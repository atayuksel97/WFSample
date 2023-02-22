// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIConsideration.h"
#include "UAIConsideration_OverlappingPickup.generated.h"

class AUAICharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_OverlappingPickup")
class UAISAMPLE_API UUAIConsideration_OverlappingPickup : public UUAIConsideration
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
