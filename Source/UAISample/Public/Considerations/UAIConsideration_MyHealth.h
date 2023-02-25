// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "UAIConsideration_MyHealth.generated.h"

class UUAIHealthComponent;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_MyHealth")
class UAISAMPLE_API UUAIConsideration_MyHealth : public UWFConsideration
{
	GENERATED_BODY()
	
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;

#if ENABLE_VISUAL_LOG
	virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;
#endif
	
	// PROPERTIES
private:
	TWeakObjectPtr<UUAIHealthComponent> HealthComp;
};
