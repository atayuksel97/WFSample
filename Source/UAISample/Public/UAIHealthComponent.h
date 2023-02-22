// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UAIHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

UCLASS(ClassGroup= "WiseFelineSample", meta=(BlueprintSpawnableComponent))
class UAISAMPLE_API UUAIHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS	
public:
	UUAIHealthComponent();

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
private:
	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* InDamageType, AController* InstigatedBy, AActor* DamageCauser);

	// GETTERS & SETTERS
public:
	FORCEINLINE void SetHealth(const float InHealth) { Health = FMath::Clamp(InHealth, 0.0f, MaxHealth); }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetMaxHealth(const float InMaxHealth) { InMaxHealth < 0.0f ? MaxHealth = 0.0f : MaxHealth = InMaxHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	// PROPERTIES
public:
	UPROPERTY(BlueprintAssignable, Category= "UAIHealthComponent")
	FOnDied OnDiedEvent;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIHealthComponent", meta=(AllowPrivateAccess= "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UAIHealthComponent", meta=(AllowPrivateAccess= "true"))
	float MaxHealth;
};
