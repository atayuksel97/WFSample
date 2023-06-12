/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "WFAction_MoveToCover.generated.h"

class UEnvQuery;
struct FEnvQueryResult;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "MoveToCover")
class WFSAMPLE_API UWFAction_MoveToCover : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;
	virtual void TickAction_Implementation(float DeltaTime) override;
	virtual void OnDeactivate_Implementation() override;
	virtual void OnUpdateTargets_Implementation() override;

#if ENABLE_VISUAL_LOG
	virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;
#endif
	
	// FUNCTIONS
public:
	void MoveToQueryResult(TSharedPtr<FEnvQueryResult> Result);
	
	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToCover")
	TObjectPtr<UEnvQuery> EnvQuery;

	UPROPERTY(VisibleAnywhere, Category= "WiseFelineSample - Action_MoveToCover")
	FVector TargetLocation;
	
	bool bIsQuerySuccessful;
};
