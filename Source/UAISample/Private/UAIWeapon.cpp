// Fill out your copyright notice in the Description page of Project Settings.

#include "UAIWeapon.h"
#include "UAIAICharacter.h"
#include "UAIPlayerCharacter.h"
#include "Components/LineBatchComponent.h"
#include "UAISampleTypes.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AUAIWeapon::AUAIWeapon() :
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

void AUAIWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	ensureMsgf(OwnerCharacter.IsValid(), TEXT("Couldn't set OwnerCharacter!"));

	if (!OwnerCharacter.IsValid())
		return;

	if (const AUAIPlayerCharacter* Character = Cast<AUAIPlayerCharacter>(OwnerCharacter))
	{
		const FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true};
		AttachToComponent(Character->SkeletalMeshComp.Get(), AttachmentRules, GripPointSocketName);
	}
	else if (const AUAIAICharacter* AICharacter = Cast<AUAIAICharacter>(OwnerCharacter))
	{
		const FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true};
		AttachToComponent(AICharacter->GetMesh(), AttachmentRules, GripPointSocketName);
	}
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UUAIateAimLocation();

	if (bShouldDrawAim)
		DrawAim();
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AUAIWeapon::StartFire()
{
	if (State != EWeaponState::NONE || ClipBulletNum == 0)
		return;

	const float TimeBetweenShots = 60.0f / RateOfFire;
	const float Delay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->GetTimeSeconds(), 0.0f);
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AUAIWeapon::Shoot, TimeBetweenShots, true, Delay);
	State = EWeaponState::FIRING;
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::EndFire()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	if (State == EWeaponState::FIRING)
		State = EWeaponState::NONE;
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::StartReloadClip()
{
	if (State != EWeaponState::NONE || ClipSize == ClipBulletNum || TotalBullets <= 0)
		return;

	State = EWeaponState::RELOADING;
	GetWorldTimerManager().SetTimer(ReloadClipTimerHandle, this, &AUAIWeapon::EndReloadClip, ReloadTime, false, ReloadTime);
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::EndReloadClip()
{
	const int32 Delta = ClipSize - ClipBulletNum;
	ClipBulletNum += TotalBullets - Delta < 0.0f ? TotalBullets : Delta;
	TotalBullets = FMath::Max(TotalBullets - Delta, 0);
	GetWorldTimerManager().ClearTimer(ReloadClipTimerHandle);
	State = EWeaponState::NONE;
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::Shoot()
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
	if (bIsHit && IsValid(Cast<AUAIAICharacter>(HitResult.GetActor())))
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

void AUAIWeapon::UUAIateAimLocation()
{
	AimStartLocation = SkeletalMeshComp->GetSocketLocation(MuzzleSocketName);

	FVector EyesLocation;
	FRotator EyesRotation;
	OwnerCharacter->GetActorEyesViewPoint(EyesLocation, EyesRotation);
	const FVector AimDirection = EyesRotation.Vector();

	AimEndLocation = EyesLocation + (AimDirection * BulletMaxDistance);
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::DrawAim() const
{
	LineBatchComp->DrawLine(AimStartLocation, AimEndLocation, DrawAimColor, SDPG_World, DrawAimShootThickness, DrawAimLifeTime);
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::DrawShoot(FVector HitLocation, const bool bIsTargetShot) const
{
	const FLinearColor Color = bIsTargetShot ? DrawShootColorOnHit : DrawShootColor;
	LineBatchComp->DrawLine(AimStartLocation, HitLocation, Color, SDPG_World, DrawAimShootThickness, DrawShootLifeTime);
}

//---------------------------------------------------------------------------------------

void AUAIWeapon::DrawImpact(FVector HitLocation, const bool bIsTargetShot) const
{
	const FLinearColor Color = bIsTargetShot ? DrawImpactColorOnHit : DrawImpactColor;
	LineBatchComp->DrawPoint(HitLocation, Color, DrawImpactSize, SDPG_World, DrawImpactLifeTime);
}
