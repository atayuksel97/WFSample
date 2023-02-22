// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UAIAIController.generated.h"

class UUAIUtilityAIComponent;
class AUAIPlayerCharacter;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample")
class UAISAMPLE_API AUAIAIController : public AAIController
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AUAIAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	// FUNCTIONS
public:
	// PROPERTIES
public:
	UPROPERTY()
	TWeakObjectPtr<AUAIPlayerCharacter> PlayerCharacter;

	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIAIController")
	TObjectPtr<UUAIUtilityAIComponent> UtilityAIComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIAIController")
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	//~END COMPONENTS
};
