// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "UAIAction_Reload.generated.h"

class AUAIWeapon;

UCLASS(ClassGroup= "WiseFelineSample")
class UAISAMPLE_API UUAIAction_Reload : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;
	virtual void TickAction_Implementation(float DeltaTime) override;
};
