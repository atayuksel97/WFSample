/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#include "Actions/WFAction_ActorMoveToTarget.h"

#include "WFCharacter.h"
#include "Kismet/GameplayStatics.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UWFAction_ActorMoveToTarget::UWFAction_ActorMoveToTarget()
{
}

//---------------------------------------------------------------------------------------

void UWFAction_ActorMoveToTarget::TickAction_Implementation(float DeltaTime)
{
	Super::TickAction_Implementation(DeltaTime);

	if (IsValid(GetControlledActor()) && IsValid(TargetActor))
	{
		const FVector NewLocation = FMath::VInterpConstantTo(GetControlledActor()->GetActorLocation(), TargetActor->GetActorLocation(), DeltaTime, 250.0f);
		GetControlledActor()->SetActorLocation(NewLocation);
	}
}

//---------------------------------------------------------------------------------------

void UWFAction_ActorMoveToTarget::OnUpdateTargets_Implementation()
{
	Super::OnUpdateTargets_Implementation();

	if (IsValid(GetControlledActor()))
	{
		ClearTargetActors();
		TArray<AActor*> OutActors;
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
		                                          GetControlledActor()->GetActorLocation(),
		                                          2000.0f,
		                                          TArray<TEnumAsByte<EObjectTypeQuery>>{ObjectTypeQuery3},
		                                          AWFCharacter::StaticClass(),
		                                          TArray<AActor*>{},
		                                          OutActors);
		TargetActors.Append(OutActors);
	}
}
