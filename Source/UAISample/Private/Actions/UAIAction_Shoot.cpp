// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UAIAction_Shoot.h"
#include "UAIAICharacter.h"
#include "UAIAIController.h"
#include "UAIWeapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

UUAIAction_Shoot::UUAIAction_Shoot()
{
	bShouldTick = true;
}

//---------------------------------------------------------------------------------------

void UUAIAction_Shoot::OnBeginPlay_Implementation()
{
	Character = Cast<AUAIAICharacter>(GetPawn());
}

//---------------------------------------------------------------------------------------

void UUAIAction_Shoot::OnActivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_Shoot::TickAction_Implementation(float DeltaTime)
{
	if (IsValid(TargetActor) && IsValid(Character.Get()) && IsValid(Character->Weapon.Get()) && Character->Weapon->ClipBulletNum > 0)
	{
		const FRotator Rotation = (TargetActor->GetActorLocation() - Character->GetActorLocation()).Rotation();
		Character->FaceRotation(Rotation, DeltaTime);

		if (Character->GetControlRotation().Equals(Rotation, 5.0f))
			Character->Fire();
		else
			Character->StopFire();
	}
	else
	{
		Finished();
	}
}

//---------------------------------------------------------------------------------------

void UUAIAction_Shoot::OnDeactivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UUAIAction_Shoot::OnUpdateTargets_Implementation()
{
	ClearTargetActors();
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetPawn()->GetActorLocation(), SphereRadius, ObjectTypesQuery, ActorClassFilter, TArray<AActor*>{GetPawn()}, OutActors);
	AddTargetActors(OutActors);
}
