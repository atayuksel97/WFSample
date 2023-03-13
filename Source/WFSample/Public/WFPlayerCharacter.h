/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "WFCharacter.h"
#include "WFPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWFHealthComponent;
class AWFWeapon;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample", DisplayName= "PlayerCharacter")
class WFSAMPLE_API AWFPlayerCharacter : public AWFCharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AWFPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
private:
	//~START INPUTS
	void LookUp(float Axis);
	void LookRight(float Axis);
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void PauseGame();
	//~END INPUTS

	// PROPERTIES
public:
	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Character")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Character")
	TObjectPtr<UCameraComponent> CameraComp;
	//~END COMPONENTS
};
