// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIAction.h"
#include "UAIAction_Pickup.generated.h"

class AUAICharacter;

UCLASS(ClassGroup= "PluginDevelopment", DisplayName= "Action_Pickup")
class UAISAMPLE_API UUAIAction_Pickup : public UUAIAction
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
