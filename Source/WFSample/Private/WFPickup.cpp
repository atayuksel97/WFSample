// Fill out your copyright notice in the Description page of Project Settings.

#include "WFPickup.h"
#include "WFCharacter.h"
#include "Components/SphereComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AWFPickup::AWFPickup()
{
	PrimaryActorTick.bCanEverTick = false;


	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	StaticMeshComp->SetCollisionObjectType(ECC_WorldStatic);
	RootComponent = StaticMeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionObjectType(ECC_WorldStatic);
	SphereComp->SetSphereRadius(50.0f);
	SphereComp->SetupAttachment(StaticMeshComp);
}

//---------------------------------------------------------------------------------------

void AWFPickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AWFPickup::BeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AWFPickup::EndOverlap);
}

//---------------------------------------------------------------------------------------

void AWFPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------------------

void AWFPickup::OnUsed_Implementation(AWFCharacter* Character)
{
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AWFPickup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWFCharacter* Character = Cast<AWFCharacter>(OtherActor);
	if (IsValid(Character))
		Character->OverlappedPickup = this;
}

//---------------------------------------------------------------------------------------

void AWFPickup::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWFCharacter* Character = Cast<AWFCharacter>(OtherActor);
	if (IsValid(Character) && Character->OverlappedPickup == this)
		Character->OverlappedPickup = nullptr;
}
