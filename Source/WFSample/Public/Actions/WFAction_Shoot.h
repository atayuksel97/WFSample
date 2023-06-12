/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "WFAction_Shoot.generated.h"

class AWFAICharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_Shoot")
class WFSAMPLE_API UWFAction_Shoot : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UWFAction_Shoot();
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;
	virtual void TickAction_Implementation(float DeltaTime) override;
	virtual void OnDeactivate_Implementation() override;
	virtual void OnUpdateTargets_Implementation() override;

	// PROPERTIES
public:
	/** Sphere overlap radius for finding targets */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_Shoot")
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_Shoot")
	TSubclassOf<AActor> ActorClassFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_Shoot")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;

	TWeakObjectPtr<AWFAICharacter> Character;
};
