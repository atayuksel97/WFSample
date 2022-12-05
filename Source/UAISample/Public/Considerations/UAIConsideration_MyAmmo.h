// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIConsideration.h"
#include "UAIConsideration_MyAmmo.generated.h"

class AUAICharacter;

UCLASS(DisplayName= "Consideration_MyAmmo")
class UAISAMPLE_API UUAIConsideration_MyAmmo : public UUAIConsideration
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;
	virtual bool IsNeededTarget_Implementation() const override;

	// PROPERTIES
private:
	TWeakObjectPtr<AUAICharacter> Character;
};
