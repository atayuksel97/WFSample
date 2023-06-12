/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WFPickup.generated.h"

class AWFCharacter;
class USphereComponent;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup= "WiseFelineSample", DisplayName= "Pickup")
class WFSAMPLE_API AWFPickup : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AWFPickup();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "WiseFelineSample - Pickup")
	void OnUsed(AWFCharacter* Character);
	virtual void OnUsed_Implementation(AWFCharacter* Character);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Pickup")
	TObjectPtr<USphereComponent> SphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "WiseFelineSample - Pickup")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
};
