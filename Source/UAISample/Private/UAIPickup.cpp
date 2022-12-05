// Fill out your copyright notice in the Description page of Project Settings.

#include "UAIPickup.h"
#include "UAICharacter.h"
#include "Components/SphereComponent.h"

//---------------------------------------------------------------------------------------
// CTOR/DTOR & VIRTUAL FUNCTIONS
//---------------------------------------------------------------------------------------

AUAIPickup::AUAIPickup()
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

void AUAIPickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AUAIPickup::BeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AUAIPickup::EndOverlap);
}

//---------------------------------------------------------------------------------------

void AUAIPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------------------

void AUAIPickup::OnUsed_Implementation(AUAICharacter* Character)
{
}

//---------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------

void AUAIPickup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUAICharacter* Character = Cast<AUAICharacter>(OtherActor);
	if (IsValid(Character))
		Character->OverlappedPickup = this;
}

//---------------------------------------------------------------------------------------

void AUAIPickup::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUAICharacter* Character = Cast<AUAICharacter>(OtherActor);
	if (IsValid(Character) && Character->OverlappedPickup == this)
		Character->OverlappedPickup = nullptr;
}
