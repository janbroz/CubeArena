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
	virtual void BeginPlay() override;

public:
	// Player movement
	void HorizontalMovement(float Amount);
	void VerticalMovement(float Amount);
	void LeftMouseButton();
	void RightMouseButton();
	void Jump();
	void ToggleStats();
	
	// Player mouse interaction
	void UpdateLocalMouseLoc();
	void AlignHeroToMouseLoc(FVector MouseLoc);
	UFUNCTION(Reliable, Server, WithValidation)
		void Server_AlignHeroToMouseLoc(FVector MouseLoc);

	// HUD and stuff
	void SpawnPlayerHUD();


public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealthValues();

public:
	TSubclassOf<class UHeroHUDWidget> HUDWidgetClass;
	class UHeroHUDWidget* HUDWidget;
	TSubclassOf<class UHeroSelectionWidget> HeroSelectionClass;
	class UHeroSelectionWidget* HeroSelectionWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		uint32 bShowingStats : 1;

private:
	uint32 bHasCharacterSelected : 1;
	uint32 bShowingScore : 1;
	uint32 bShowingInventory : 1;
};
