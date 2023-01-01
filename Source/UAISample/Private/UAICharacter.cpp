// Fill out your copyright notice in the Description page of Project Settings.

#include "UAICharacter.h"
#include "UAIHealthComponent.h"
#include "UAIPickup.h"
#include "UAIWeapon.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AUAICharacter::AUAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;

	HealthComp = CreateDefaultSubobject<UUAIHealthComponent>(TEXT("HealthComponent"));
	HealthComp->SetMaxHealth(100.0f);
	HealthComp->SetHealth(100.0f);
}

//---------------------------------------------------------------------------------------

void AUAICharacter::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(WeaponClass, TEXT("WeaponClass haven't been set"));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	Weapon = GetWorld()->SpawnActor<AUAIWeapon>(WeaponClass ? *WeaponClass : AUAIWeapon::StaticClass(), SpawnParameters);
}

//---------------------------------------------------------------------------------------

void AUAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------------------

void AUAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUAICharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AUAICharacter::StopFire);
	PlayerInputComponent->BindAction("ReloadWeapon", IE_Pressed, this, &AUAICharacter::ReloadWeapon);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AUAICharacter::Pickup);
}

//---------------------------------------------------------------------------------------

void AUAICharacter::Fire()
{
	if (IsValid(Weapon))
		Weapon->StartFire();
}

//---------------------------------------------------------------------------------------

void AUAICharacter::StopFire()
{
	if (IsValid(Weapon))
		Weapon->EndFire();
}

//---------------------------------------------------------------------------------------

void AUAICharacter::ReloadWeapon()
{
	if (IsValid(Weapon))
		Weapon->StartReloadClip();
}

//---------------------------------------------------------------------------------------

void AUAICharacter::Pickup()
{
	if (IsValid(OverlappedPickup.Get()))
	{
		OverlappedPickup->OnUsed(this);
		OverlappedPickup = nullptr;
	}
}
