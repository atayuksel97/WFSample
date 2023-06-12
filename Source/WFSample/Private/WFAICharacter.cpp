/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
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

