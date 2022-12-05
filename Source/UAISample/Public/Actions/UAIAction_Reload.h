// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIAction.h"
#include "UAIAction_Reload.generated.h"

class AUAIWeapon;

UCLASS()
class UAISAMPLE_API UUAIAction_Reload : public UUAIAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;
	virtual void TickAction_Implementation(float DeltaTime) override;
};
