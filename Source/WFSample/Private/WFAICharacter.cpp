/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/


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

