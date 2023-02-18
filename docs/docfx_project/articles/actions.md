# Actions

Actions are the most important part of a utility AI system alongside considerations.
An action is a concrete and most of the time atomic unit of work which an agent can do. Shoot, Find health pack, Find cover, Take cover in the found cover, eat food and Choose the best camera to shot the scene with are all examples of actions.
However an action doesn't have to be low level and can be pretty high level, you can have a hierarchy of them in your game and for example have a set of actions for groups of NPCs which can be attack the target, spread members in the room, defend sensitive points, find weak spots by bombing every place and then some NPC actions which take command from the group so when the group chooses to attack the target, a member NPC might execute its shoot action or move toward target action or cover the attackers.

To create an action you should inherit a class in C++ or blueprint from `UWFAction`:

Here is an action which moves an actor toward a target.

```

#include "Actions/UAIAction_ActorMoveToTarget.h"

#include "UAICharacter.h"
#include "Kismet/GameplayStatics.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UUAIAction_ActorMoveToTarget::UUAIAction_ActorMoveToTarget()
{
}

//gets called every tick when this action is chosen to execute for an AI

void UUAIAction_ActorMoveToTarget::TickAction_Implementation(float DeltaTime)
{
	Super::TickAction_Implementation(DeltaTime);

	if (IsValid(GetControlledActor()) && IsValid(TargetActor))
	{
		const FVector NewLocation = FMath::VInterpConstantTo(GetControlledActor()->GetActorLocation(), TargetActor->GetActorLocation(), DeltaTime, 250.0f);
		GetControlledActor()->SetActorLocation(NewLocation);
	}
}

//updates the list of potential targets which the action should pick from

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

```

There are several things to note:

First of all there are two types of actions, targeted and none-targeted. Targeted ones are those which work on a target like shoot and eat pack. This action is targeted.
None-targeted ones are those which don't have a target like idle or useHealthPackFromInventory. 

Second there are a set of callbacks in an action which you can override. `OnBeginPlay()` is called as soon as the action is added to the `WfUtilityAIComponent` or in the first frame if the behavior is in the `WFUtilityAIComponent` when the actor is created.
`OnTick()` is called every frame when the action is the chosen action to be executed for the actor because it has the highest score. 
`OnActivate` is called when the action is chosen to become the action for the actor before the first tick.
`OnDeactivate` is called when the action is no longer the chosen one to be executed and will be replaced by another action this frame.

If the action is targeted then the `Target` field has the best target in it which you should shoot at, eat or move toward or do whatever which is right for your action.
An action becomes a targeted one if you choose the box in the behavior editor window for it and then `OnUpdateTarget()` is called for you to fill the list of targets in.
A targeted action means all considerations are calculated for all targets which you gave to the action in the `OnUpdateTargets()` callback and the one with the highest score is set in the `Target` field.
`OnUpdateTargets()` is called once per `UpdateTargetsInterval` seconds, which its frequency is chosen in the action itself unlike the `EvalulationIntervalTime` which is the time between action score calculations and is set in the `WFUtilityAIComponent` for all actions.

The scores of all actions are calculated once per `WFUtilityAIComponent::EvaluationIntervalTime` and then the highest score action will be selected to run.
Here you just define how the action will execute and that's it.

When filling the list of targets, you can fill it with actors with whatever method you want. You can use EQS, your own special systems for the game or simple raycast or cahced lists in a manager script. The only important thing is for the list to be accurate and not take much time to generate.

You don't have to clear and rebuild the list of targets every time either but in that case you should be careful to not add something multiple times and also to remove objects which are not good target candidates as well.
Also if your action does not need any targets, You don't need to add any targets in `OnUpdateTargets()`.

For more information, browse the sample and the source code.