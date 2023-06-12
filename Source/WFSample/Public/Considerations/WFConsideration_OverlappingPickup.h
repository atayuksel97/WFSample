/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFConsideration.h"
#include "WFConsideration_OverlappingPickup.generated.h"

class AWFCharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Consideration_OverlappingPickup")
class WFSAMPLE_API UWFConsideration_OverlappingPickup : public UWFConsideration
{
	GENERATED_BODY()
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual float GetValue_Implementation(const AActor* InTargetActor) override;

	// PROPERTIES
public:
	TObjectPtr<AWFCharacter> Character;
};
