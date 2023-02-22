﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UAICharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UUAIHealthComponent;
class AUAIWeapon;
class AUAIPickup;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample", DisplayName= "UAICharacter")
class UAISAMPLE_API AUAICharacter : public ACharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AUAICharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Fire();
	virtual void StopFire();
	virtual void ReloadWeapon();
	virtual void Pickup();

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:
	UFUNCTION(BlueprintNativeEvent, Category= "WiseFelineSample - UAICharacter")
	void OnDied();
	void OnDied_Implementation();

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - UAICharacter")
	TSubclassOf<AUAIWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - UAICharacter")
	TObjectPtr<AUAIWeapon> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="WiseFelineSample - UAICharacter")
	TObjectPtr<AUAIPickup> OverlappedPickup;

	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - UAICharacter")
	TObjectPtr<UUAIHealthComponent> HealthComp;
	//~END COMPONENTS
};
