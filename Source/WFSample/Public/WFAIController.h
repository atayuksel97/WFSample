// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WFAIController.generated.h"

class UWFBrainComponent;
class AWFPlayerCharacter;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample")
class WFSAMPLE_API AWFAIController : public AAIController
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AWFAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	// FUNCTIONS
public:
	// PROPERTIES
public:
	UPROPERTY()
	TWeakObjectPtr<AWFPlayerCharacter> PlayerCharacter;

	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - AIController")
	TObjectPtr<UWFBrainComponent> WFBrainComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - AIController")
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	//~END COMPONENTS
};
