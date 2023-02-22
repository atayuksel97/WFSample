// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAIAction.h"
#include "UAIAction_MoveToTargetActor.generated.h"

class UAITask_MoveTo;
class UNavigationQueryFilter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_MoveToTargetActor")
class UAISAMPLE_API UUAIAction_MoveToTargetActor : public UUAIAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UUAIAction_MoveToTargetActor();
	virtual void OnBeginPlay_Implementation() override;
	virtual void OnActivate_Implementation() override;
	virtual void TickAction_Implementation(float DeltaTime) override;
	virtual void OnDeactivate_Implementation() override;
	virtual void OnUpdateTargets_Implementation() override;

	// PROPERTIES
	/** Add pawn's radius to AcceptanceRadius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	bool bStopOnOverlap;

	/** Use navigation data to calculate path (otherwise it will go in straight line)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	bool bUsePathfinding;

	/** Set focus related flag: bAllowStrafe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	bool bCanStrafe;

	/** Use incomplete path when goal can't be reached */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	bool bAllowPartialPaths;

	/** Project location on navigation data before using it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	bool bProjectDestinationToNavigation;

	/** Finish move if pawn gets close enough */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	float AcceptanceRadius;

	/** Navigation filter for pathfinding adjustments. If none specified DefaultNavigationFilterClass will be used */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	TSubclassOf<UNavigationQueryFilter> NavigationQueryFilterClass;

	/** Sphere overlap radius for finding targets */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	TSubclassOf<AActor> ActorClassFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Action_MoveToTargetActor")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
};
