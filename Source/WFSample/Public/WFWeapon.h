/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WFWeapon.generated.h"

class AWFPlayerCharacter;

UENUM()
enum class EWeaponState
{
	NONE,
	FIRING,
	RELOADING
};

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample")
class WFSAMPLE_API AWFWeapon : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AWFWeapon();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:
	void StartFire();
	void EndFire();
	void StartReloadClip();
	void EndReloadClip();

private:
	void Shoot();
	void CalculateAimLocation();
	void DrawAim() const;
	void DrawShoot(FVector HitLocation, const bool bIsTargetShot) const;
	void DrawImpact(FVector HitLocation, const bool bIsTargetShot) const;

	// PROPERTIES
public:
	/** The size of the weapon's clip. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 ClipSize;

	/** The number of bullets currently in the weapon's clip. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 ClipBulletNum;

	/** The total number of bullets the weapon has (both in the clip and in reserve). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 TotalBullets;

	/** The maximum number of bullets the weapon can hold (both in the clip and in reserve). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 MaxBullets;

	/** The spread of each bullet when fired from the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float BulletSpread;

	/** The amount of damage each bullet does when it hits something. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float Damage;

	/** The type of damage inflicted by the weapon's bullets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	TSubclassOf<UDamageType> DamageType;

	/** The number of bullets that can be fired per minute, ex: AK47= 600 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float RateOfFire;

	/** The amount of time it takes to reload the weapon's clip. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float ReloadTime;

	/** The maximum distance that a bullet can travel before it is destroyed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float BulletMaxDistance;

	/** The current state of the weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	EWeaponState State;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FName GripPointSocketName;

	/** Whether or not the weapon should draw a trace when aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	bool bShouldDrawAim;

	/** Whether or not the weapon should draw a trace when shooting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	bool bShouldDrawShoot;

	/** Whether or not the weapon should draw a point where the bullet hits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	bool bShouldDrawImpact;

	/** The thickness of the AimShoot trace line. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawAimShootThickness;

	/** The size of the HitImpact point. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawImpactSize;

	/** The time in seconds that the aim line remains visible. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawAimLifeTime;

	/** The time in seconds that the shoot line remains visible. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawShootLifeTime;

	/** The time in seconds that the impact line remains visible. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawImpactLifeTime;

	/** The color of the aim line. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawAimColor;

	/** The color of the shoot line. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawShootColor;

	/** The color of the shoot line if it hits target. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawShootColorOnHit;

	/** The color of the impact effect when hitting a surface. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawImpactColor;

	/** The color of the impact effect when hitting a surface and dealing damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawImpactColorOnHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FVector AimStartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FVector AimEndLocation;

	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	TObjectPtr<ULineBatchComponent> LineBatchComp;
	//~END COMPONENTS

private:
	float LastFireTime;

	UPROPERTY()
	TWeakObjectPtr<ACharacter> OwnerCharacter;

	FTimerHandle ShootTimerHandle;

	FTimerHandle ReloadClipTimerHandle;
};
