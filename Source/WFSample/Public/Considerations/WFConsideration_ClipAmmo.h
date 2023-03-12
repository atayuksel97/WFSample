// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "WFConsideration_ClipAmmo.generated.h"

class AWFCharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_MyClipAmmo")
class WFSAMPLE_API UWFConsideration_ClipAmmo : public UWFConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;

	// PROPERTIES
public:
	TObjectPtr<const AWFCharacter> Character;
};
