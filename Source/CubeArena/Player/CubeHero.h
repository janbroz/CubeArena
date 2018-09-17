// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CubeHero.generated.h"

UCLASS()
class CUBEARENA_API ACubeHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACubeHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
public:
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class USpringArmComponent* CameraArm;

	
};
