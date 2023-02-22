// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIAction.h"
#include "UAIAction_MoveToCover.generated.h"

class UEnvQuery;
struct FEnvQueryResult;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "MoveToCover")
class UAISAMPLE_API UUAIAction_MoveToCover : public UUAIAction
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Action_MoveToCover")
	TObjectPtr<UEnvQuery> EnvQuery;

	UPROPERTY(VisibleAnywhere, Category= "Action_MoveToCover")
	FVector TargetLocation;
	
	bool bIsQuerySuccessful;
};
