/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "WFAction_Reload.generated.h"

class AWFWeapon;

UCLASS(ClassGroup= "WiseFelineSample")
class WFSAMPLE_API UWFAction_Reload : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;
	virtual void TickAction_Implementation(float DeltaTime) override;
};
