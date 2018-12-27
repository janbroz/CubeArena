// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class CUBEARENA_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable)
		void TraceBlade();
	UFUNCTION(BlueprintCallable)
		void ToggleTracingBlade();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WeaponInformation)
		int32 Weight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WeaponInformation)
		uint32 bTracingBlade : 1;

	// The pawn that has the weapon currently equiped
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WeaponInformation)
		class ACubeHero* CharacterOwner;

	// The actors we hit with the weapon. Verify if they are not in the array
	// Before applying an effect.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WeaponInformation)
		TArray<AActor*> HitActors;

};
