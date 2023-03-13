/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/


#include "WFPlayerCharacter.h"
#include "WFHealthComponent.h"
#include "WFWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AWFPlayerCharacter::AWFPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComp->SetupAttachment(CameraComp);
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &AWFPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AWFPlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AWFPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWFPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &AWFPlayerCharacter::PauseGame);
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::LookRight(float Axis)
{
	AddControllerYawInput(Axis);
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

//---------------------------------------------------------------------------------------

void AWFPlayerCharacter::PauseGame()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,TEXT("UnPaused"));
		}
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,TEXT("Paused"));
		}
	}
}
