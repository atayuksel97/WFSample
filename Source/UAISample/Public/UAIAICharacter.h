// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAICharacter.h"
#include "UAIAICharacter.generated.h"

class AUAIWeapon;
class UUAIHealthComponent;

UCLASS(Blueprintable, ClassGroup= "PluginDevelopment", DisplayName= "AICharacter")
class UAISAMPLE_API AUAIAICharacter : public AUAICharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AUAIAICharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
