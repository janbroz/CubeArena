// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Player/CubeHero.h"

AWeapon::AWeapon()
{
	bTracingBlade = false;
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTracingBlade)
	{
		TraceBlade();
	}
}

void AWeapon::TraceBlade()
{
	//UE_LOG(LogTemp, Warning, TEXT("Weapon is tracing stuff"));

	FVector WeaponHandle = MeshComponent->GetSocketLocation("WeaponHandleSocket");
	FVector WeaponTip = MeshComponent->GetSocketLocation("WeaponTipSocket");

	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByChannel(HitResults, WeaponHandle, WeaponTip, ECollisionChannel::ECC_Camera);
	
	// This one is to see the ray trace in debugging mode.
	//DrawDebugLine(GetWorld(), WeaponHandle, WeaponTip, FColor::Red, false, 5.f, 2, 8.f);

	for (FHitResult& Hit : HitResults)
	{
		if (Hit.bBlockingHit)
		{
			AActor* ValidActor = Hit.GetActor();
			if (ValidActor)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Actor hit is: %s"), *ValidActor->GetName());
				bool bAlreadyDamaged = HitActors.Contains(ValidActor);
				HitActors.AddUnique(ValidActor);
				if (CharacterOwner && !bAlreadyDamaged)
				{
					TArray<AActor*> HitStuff;
					HitStuff.Add(ValidActor);

					CharacterOwner->NotifyHitActorsByWeapon(HitStuff);
				}
			}
		}
	}
}

void AWeapon::ToggleTracingBlade()
{
	bTracingBlade = !bTracingBlade;

	if (!bTracingBlade)
	{
		//UE_LOG(LogTemp, Warning, TEXT("It should empty the array"));
		HitActors.Empty();
	}
}
