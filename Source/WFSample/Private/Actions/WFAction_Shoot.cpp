/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/

#include "Actions/WFAction_Shoot.h"
#include "WFAICharacter.h"
#include "WFSampleTypes.h"
#include "WFWeapon.h"
#include "Kismet/KismetSystemLibrary.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

UWFAction_Shoot::UWFAction_Shoot()
{
	bShouldTick = true;
}

//---------------------------------------------------------------------------------------

void UWFAction_Shoot::OnBeginPlay_Implementation()
{
	Character = Cast<AWFAICharacter>(GetControlledActor());
}

//---------------------------------------------------------------------------------------

void UWFAction_Shoot::OnActivate_Implementation()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_Shoot::TickAction_Implementation(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_Shoot::TickAction_Implementation)
	
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

void UWFAction_Shoot::OnDeactivate_Implementation()
{
	if(IsValid(Character.Get()))
	Character->StopFire();
}

//---------------------------------------------------------------------------------------

void UWFAction_Shoot::OnUpdateTargets_Implementation()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UWFAction_Shoot::OnUpdateTargets_Implementation)
	
	TargetActors.Reset();
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetControlledActor()->GetActorLocation(), SphereRadius, ObjectTypesQuery, ActorClassFilter, TArray<AActor*>{GetControlledActor()}, OutActors);
	TargetActors.Append(OutActors);
}
