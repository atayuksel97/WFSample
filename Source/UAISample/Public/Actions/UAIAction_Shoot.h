// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFAction.h"
#include "UAIAction_Shoot.generated.h"

class AUAIAICharacter;

UCLASS(ClassGroup= "WiseFelineSample", DisplayName= "Action_Shoot")
class UAISAMPLE_API UUAIAction_Shoot : public UWFAction
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UUAIAction_Shoot();
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

	TWeakObjectPtr<AUAIAICharacter> Character;
};
