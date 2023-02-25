// Fill out your copyright notice in the Description page of Project Settings.


#include "WFAICharacter.h"

#include "WFHealthComponent.h"
#include "WFWeapon.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AWFAICharacter::AWFAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

//---------------------------------------------------------------------------------------

void AWFAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------------------

void AWFAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

