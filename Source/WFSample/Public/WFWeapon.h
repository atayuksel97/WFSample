// Fill out your copyright notice in the Description page of Project Settings.

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 ClipSize;

	/** Number of bullets in the current Clip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 ClipBulletNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 TotalBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	int32 MaxBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float BulletSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	TSubclassOf<UDamageType> DamageType;

	/** Number of bullets can shot per minutes, ex: AK47= 600 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float BulletMaxDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	EWeaponState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FName GripPointSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	bool bShouldDrawAim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	bool bShouldDrawShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	bool bShouldDrawImpact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawAimShootThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawImpactSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawAimLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawShootLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	float DrawImpactLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawAimColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawShootColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawShootColorOnHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Weapon")
	FLinearColor DrawImpactColor;

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
