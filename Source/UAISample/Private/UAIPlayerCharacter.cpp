// Fill out your copyright notice in the Description page of Project Settings.


#include "UAIPlayerCharacter.h"
#include "UAIHealthComponent.h"
#include "UAIWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AUAIPlayerCharacter::AUAIPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComp->SetupAttachment(CameraComp);
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &AUAIPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AUAIPlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AUAIPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUAIPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &AUAIPlayerCharacter::PauseGame);
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::LookRight(float Axis)
{
	AddControllerYawInput(Axis);
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

//---------------------------------------------------------------------------------------

void AUAIPlayerCharacter::PauseGame()
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
