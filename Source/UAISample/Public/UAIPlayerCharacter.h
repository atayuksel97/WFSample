// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAICharacter.h"
#include "UAIPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UUAIHealthComponent;
class AUAIWeapon;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample", DisplayName= "PlayerCharacter")
class UAISAMPLE_API AUAIPlayerCharacter : public AUAICharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AUAIPlayerCharacter();
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - UAICharacter")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - UAICharacter")
	TObjectPtr<UCameraComponent> CameraComp;
	//~END COMPONENTS
};
