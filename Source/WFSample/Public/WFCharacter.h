/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WFCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWFHealthComponent;
class AWFWeapon;
class AWFPickup;

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample", DisplayName= "Character")
class WFSAMPLE_API AWFCharacter : public ACharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AWFCharacter();
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
	UFUNCTION(BlueprintNativeEvent, Category= "WiseFelineSample - Character")
	void OnDied();
	void OnDied_Implementation();

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Character")
	TSubclassOf<AWFWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Character")
	TObjectPtr<AWFWeapon> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="WiseFelineSample - Character")
	TObjectPtr<AWFPickup> OverlappedPickup;

	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Character")
	TObjectPtr<UWFHealthComponent> HealthComp;
	//~END COMPONENTS
};
