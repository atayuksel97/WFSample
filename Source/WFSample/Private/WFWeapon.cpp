/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#include "WFWeapon.h"
#include "WFAICharacter.h"
#include "WFPlayerCharacter.h"
#include "Components/LineBatchComponent.h"
#include "WFSampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AWFWeapon::AWFWeapon() :
	ClipSize{30},
	ClipBulletNum{ClipSize},
	TotalBullets{60},
	MaxBullets{120},
	BulletSpread{2.0f},
	Damage{20.0f},
	RateOfFire{600},
	ReloadTime{3.0f},
	BulletMaxDistance{3000},
	MuzzleSocketName{TEXT("Muzzle")},
	GripPointSocketName{TEXT("GripPoint")},
	bShouldDrawAim{true},
	bShouldDrawShoot{true},
	bShouldDrawImpact{true},
	DrawAimShootThickness{2.0f},
	DrawImpactSize{10.0f},
	DrawAimLifeTime{0.02f},
	DrawShootLifeTime{1.0f},
	DrawImpactLifeTime{5.0f},
	DrawAimColor{FLinearColor::Green},
	DrawShootColor{FLinearColor::Yellow},
	DrawShootColorOnHit{FLinearColor::Red},
	DrawImpactColor{FLinearColor::White},
	DrawImpactColorOnHit{FLinearColor::Blue}
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SkeletalMeshComp;

	LineBatchComp = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatchComponent"));
	LineBatchComp->SetupAttachment(SkeletalMeshComp);
}

//---------------------------------------------------------------------------------------

void AWFWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	ensureMsgf(OwnerCharacter.IsValid(), TEXT("Couldn't set OwnerCharacter!"));

	if (!OwnerCharacter.IsValid())
		return;

	if (const AWFPlayerCharacter* Character = Cast<AWFPlayerCharacter>(OwnerCharacter))
	{
		const FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true};
		AttachToComponent(Character->SkeletalMeshComp.Get(), AttachmentRules, GripPointSocketName);
	}
	else if (const AWFAICharacter* AICharacter = Cast<AWFAICharacter>(OwnerCharacter))
	{
		const FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true};
		AttachToComponent(AICharacter->GetMesh(), AttachmentRules, GripPointSocketName);
	}
}

//---------------------------------------------------------------------------------------

void AWFWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateAimLocation();

	if (bShouldDrawAim)
		DrawAim();
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AWFWeapon::StartFire()
{
	if (State != EWeaponState::NONE || ClipBulletNum == 0)
		return;

	const float TimeBetweenShots = 60.0f / RateOfFire;
	const float Delay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->GetTimeSeconds(), 0.0f);
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AWFWeapon::Shoot, TimeBetweenShots, true, Delay);
	State = EWeaponState::FIRING;
}

//---------------------------------------------------------------------------------------

void AWFWeapon::EndFire()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	if (State == EWeaponState::FIRING)
		State = EWeaponState::NONE;
}

//---------------------------------------------------------------------------------------

void AWFWeapon::StartReloadClip()
{
	if (State != EWeaponState::NONE || ClipSize == ClipBulletNum || TotalBullets <= 0)
		return;

	State = EWeaponState::RELOADING;
	GetWorldTimerManager().SetTimer(ReloadClipTimerHandle, this, &AWFWeapon::EndReloadClip, ReloadTime, false, ReloadTime);
}

//---------------------------------------------------------------------------------------

void AWFWeapon::EndReloadClip()
{
	const int32 Delta = ClipSize - ClipBulletNum;
	ClipBulletNum += TotalBullets - Delta < 0.0f ? TotalBullets : Delta;
	TotalBullets = FMath::Max(TotalBullets - Delta, 0);
	GetWorldTimerManager().ClearTimer(ReloadClipTimerHandle);
	State = EWeaponState::NONE;
}

//---------------------------------------------------------------------------------------

void AWFWeapon::Shoot()
{
	if (ClipBulletNum == 0)
	{
		EndFire();
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams{TEXT("Shoot"), true, OwnerCharacter.Get()};
	CollisionQueryParams.AddIgnoredActor(this);

	const float SpreadRadian = FMath::DegreesToRadians(BulletSpread);
	FVector Direction = FMath::VRandCone(OwnerCharacter->GetViewRotation().Vector(), SpreadRadian, SpreadRadian);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, AimStartLocation, AimStartLocation + Direction * BulletMaxDistance, COLLISION_WEAPON, CollisionQueryParams);
	if (bIsHit && IsValid(Cast<AWFAICharacter>(HitResult.GetActor())))
	{
		TSubclassOf<UDamageType> DamageTypeClass = DamageType ? *DamageType : UDamageType::StaticClass();
		HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(DamageTypeClass), OwnerCharacter->GetController(), this);
	}
	else
	{
		// HitActor isn't enemy
		bIsHit = false;
	}

	if (bShouldDrawShoot)
		DrawShoot(HitResult.ImpactPoint, bIsHit);

	if (bShouldDrawImpact)
		DrawImpact(HitResult.ImpactPoint, bIsHit);

	LastFireTime = GetWorld()->TimeSeconds;
	ClipBulletNum--;
}

//---------------------------------------------------------------------------------------

void AWFWeapon::CalculateAimLocation()
{
	if(IsValid(OwnerCharacter.Get()))
	{
		AimStartLocation = SkeletalMeshComp->GetSocketLocation(MuzzleSocketName);

		FVector EyesLocation;
		FRotator EyesRotation;
		OwnerCharacter->GetActorEyesViewPoint(EyesLocation, EyesRotation);
		const FVector AimDirection = EyesRotation.Vector();

		AimEndLocation = EyesLocation + (AimDirection * BulletMaxDistance);
	}
}

//---------------------------------------------------------------------------------------

void AWFWeapon::DrawAim() const
{
	LineBatchComp->DrawLine(AimStartLocation, AimEndLocation, DrawAimColor, SDPG_World, DrawAimShootThickness, DrawAimLifeTime);
}

//---------------------------------------------------------------------------------------

void AWFWeapon::DrawShoot(FVector HitLocation, const bool bIsTargetShot) const
{
	const FLinearColor Color = bIsTargetShot ? DrawShootColorOnHit : DrawShootColor;
	LineBatchComp->DrawLine(AimStartLocation, HitLocation, Color, SDPG_World, DrawAimShootThickness, DrawShootLifeTime);
}

//---------------------------------------------------------------------------------------

void AWFWeapon::DrawImpact(FVector HitLocation, const bool bIsTargetShot) const
{
	const FLinearColor Color = bIsTargetShot ? DrawImpactColorOnHit : DrawImpactColor;
	LineBatchComp->DrawPoint(HitLocation, Color, DrawImpactSize, SDPG_World, DrawImpactLifeTime);
}
