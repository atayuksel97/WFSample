/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#include "WFCharacter.h"
#include "WFHealthComponent.h"
#include "WFPickup.h"
#include "WFWeapon.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AWFCharacter::AWFCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;

	HealthComp = CreateDefaultSubobject<UWFHealthComponent>(TEXT("HealthComponent"));
	HealthComp->SetMaxHealth(100.0f);
	HealthComp->SetHealth(100.0f);
}

//---------------------------------------------------------------------------------------

void AWFCharacter::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(WeaponClass, TEXT("WeaponClass haven't been set"));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	Weapon = GetWorld()->SpawnActor<AWFWeapon>(WeaponClass ? *WeaponClass : AWFWeapon::StaticClass(), SpawnParameters);

	HealthComp->OnDiedEvent.AddDynamic(this, &AWFCharacter::OnDied);
}

//---------------------------------------------------------------------------------------

void AWFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------------------

void AWFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWFCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AWFCharacter::StopFire);
	PlayerInputComponent->BindAction("ReloadWeapon", IE_Pressed, this, &AWFCharacter::ReloadWeapon);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AWFCharacter::Pickup);
}

//---------------------------------------------------------------------------------------

void AWFCharacter::Fire()
{
	if (IsValid(Weapon))
		Weapon->StartFire();
}

//---------------------------------------------------------------------------------------

void AWFCharacter::StopFire()
{
	if (IsValid(Weapon))
		Weapon->EndFire();
}

//---------------------------------------------------------------------------------------

void AWFCharacter::ReloadWeapon()
{
	if (IsValid(Weapon))
		Weapon->StartReloadClip();
}

//---------------------------------------------------------------------------------------

void AWFCharacter::Pickup()
{
	if (IsValid(OverlappedPickup.Get()))
	{
		OverlappedPickup->OnUsed(this);
		OverlappedPickup = nullptr;
	}
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AWFCharacter::OnDied_Implementation()
{
	Weapon->Destroy();
	Destroy();
}
