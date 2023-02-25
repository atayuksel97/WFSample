// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFCharacter.h"
#include "WFAICharacter.generated.h"

class AWFWeapon;
class UWFHealthComponent;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample", DisplayName= "AICharacter")
class WFSAMPLE_API AWFAICharacter : public AWFCharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AWFAICharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
