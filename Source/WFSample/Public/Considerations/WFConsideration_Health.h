// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "WFConsideration_Health.generated.h"

class AWFCharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_MyHealth")
class WFSAMPLE_API UWFConsideration_Health : public UWFConsideration
{
	GENERATED_BODY()
	
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;

#if ENABLE_VISUAL_LOG
	virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;
#endif
	
	// PROPERTIES
private:
	TObjectPtr<const AWFCharacter> Character;
};
