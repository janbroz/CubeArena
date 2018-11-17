// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CUBEARENA_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMenuPlayerController();
	virtual void BeginPlay() override;
	
public:
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;
	class UMainMenuWidget* MainMenuWidget;

	TSubclassOf<class ULobbyWidget> LobbyWidgetClass;
	class ULobbyWidget* LobbyWidget;


public:
	UFUNCTION(BlueprintCallable)
		void ShowLobby();
};
