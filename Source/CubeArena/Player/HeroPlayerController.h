// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CUBEARENA_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AHeroPlayerController();
	
	
public:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Possess(APawn* NewPawn) override;
	virtual void UnPossess() override;

public:
	// Player movement
	void HorizontalMovement(float Amount);
	void VerticalMovement(float Amount);
	void LeftMouseButton();
	void RightMouseButton();
	void Jump();
	
	// Player mouse interaction
	void UpdateLocalMouseLoc();
	void AlignHeroToMouseLoc(FVector MouseLoc);
	UFUNCTION(Reliable, Server, WithValidation)
		void Server_AlignHeroToMouseLoc(FVector MouseLoc);

	// HUD and stuff
public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealthValues();

public:
	TSubclassOf<class UHeroHUDWidget> HUDWidgetClass;
	class UHeroHUDWidget* HUDWidget;

};
