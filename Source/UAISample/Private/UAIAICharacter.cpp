// Fill out your copyright notice in the Description page of Project Settings.


#include "UAIAICharacter.h"

#include "UAIHealthComponent.h"
#include "UAIWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AUAIAICharacter::AUAIAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

//---------------------------------------------------------------------------------------

void AUAIAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------------------

void AUAIAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

