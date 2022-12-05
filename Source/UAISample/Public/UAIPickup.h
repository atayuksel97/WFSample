// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UAIPickup.generated.h"

class AUAICharacter;
class USphereComponent;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup= "PluginDevelopment", DisplayName= "Pickup")
class UAISAMPLE_API AUAIPickup : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AUAIPickup();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Pickup")
	void OnUsed(AUAICharacter* Character);
	virtual void OnUsed_Implementation(AUAICharacter* Character);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pickup")
	TObjectPtr<USphereComponent> SphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pickup")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
};
