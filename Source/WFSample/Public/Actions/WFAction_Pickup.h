/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "WFAction_Pickup.generated.h"

class AWFCharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_Pickup")
class WFSAMPLE_API UWFAction_Pickup : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;

	// PROPERTIES
public:
	TWeakObjectPtr<AWFCharacter> Character;
};
