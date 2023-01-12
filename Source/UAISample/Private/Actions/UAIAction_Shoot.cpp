// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UAIAction_Shoot.h"
#include "UAIAICharacter.h"
#include "UAISampleTypes.h"
#include "UAIWeapon.h"
#include "Kismet/KismetSystemLibrary.h"

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
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIAction_Shoot::TickAction_Implementation)
	
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
	if(IsValid(Character.Get()))
	Character->StopFire();
}

//---------------------------------------------------------------------------------------

void UUAIAction_Shoot::OnUpdateTargets_Implementation()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUAIAction_Shoot::OnUpdateTargets_Implementation)
	
	TargetActors.Reset();
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetPawn()->GetActorLocation(), SphereRadius, ObjectTypesQuery, ActorClassFilter, TArray<AActor*>{GetPawn()}, OutActors);
	TargetActors.Append(OutActors);
}
