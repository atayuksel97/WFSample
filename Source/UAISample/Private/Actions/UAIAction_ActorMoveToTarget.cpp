// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UAIAction_ActorMoveToTarget.h"

#include "UAICharacter.h"
#include "Kismet/GameplayStatics.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UUAIAction_ActorMoveToTarget::UUAIAction_ActorMoveToTarget()
{
	bShouldTick = true;
	bIsInterruptible = true;
	bHasTargetActor = true;
	bUseMomentumOnSelectedTargetActor = true;
}

//---------------------------------------------------------------------------------------

void UUAIAction_ActorMoveToTarget::TickAction_Implementation(float DeltaTime)
{
	Super::TickAction_Implementation(DeltaTime);

	if (IsValid(GetControlledActor()) && IsValid(TargetActor))
	{
		const FVector NewLocation = FMath::VInterpConstantTo(GetControlledActor()->GetActorLocation(), TargetActor->GetActorLocation(), DeltaTime, 250.0f);
		GetControlledActor()->SetActorLocation(NewLocation);
	}
}

//---------------------------------------------------------------------------------------

void UUAIAction_ActorMoveToTarget::OnUpdateTargets_Implementation()
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
		                                          AUAICharacter::StaticClass(),
		                                          TArray<AActor*>{},
		                                          OutActors);
		TargetActors.Append(OutActors);
	}
}
