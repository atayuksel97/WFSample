// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UAIWeapon.generated.h"

class AUAIPlayerCharacter;

UENUM()
enum class EWeaponState
{
	NONE,
	FIRING,
	RELOADING
};

UCLASS(Blueprintable, ClassGroup= "WiseFelineSample")
class UAISAMPLE_API AUAIWeapon : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AUAIWeapon();
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	int32 ClipSize;

	/** Number of bullets in the current Clip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	int32 ClipBulletNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	int32 TotalBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	int32 MaxBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float BulletSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	TSubclassOf<UDamageType> DamageType;

	/** Number of bullets can shot per minutes, ex: AK47= 600 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float BulletMaxDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	EWeaponState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FName GripPointSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	bool bShouldDrawAim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	bool bShouldDrawShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	bool bShouldDrawImpact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float DrawAimShootThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float DrawImpactSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float DrawAimLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float DrawShootLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	float DrawImpactLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FLinearColor DrawAimColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FLinearColor DrawShootColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FLinearColor DrawShootColorOnHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FLinearColor DrawImpactColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FLinearColor DrawImpactColorOnHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FVector AimStartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	FVector AimEndLocation;

	//~START COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIWeapon")
	TObjectPtr<ULineBatchComponent> LineBatchComp;
	//~END COMPONENTS

private:
	float LastFireTime;

	UPROPERTY()
	TWeakObjectPtr<ACharacter> OwnerCharacter;

	FTimerHandle ShootTimerHandle;

	FTimerHandle ReloadClipTimerHandle;
};
