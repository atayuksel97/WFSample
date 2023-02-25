// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "UAIAction_Pickup.generated.h"

class AUAICharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_Pickup")
class UAISAMPLE_API UUAIAction_Pickup : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;

	// PROPERTIES
public:
	TWeakObjectPtr<AUAICharacter> Character;
};
