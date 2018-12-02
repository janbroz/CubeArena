// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CubePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CUBEARENA_API ACubePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ACubePlayerState();
	
public:
	UFUNCTION(BlueprintCallable)
		void SelectCharacter(TSubclassOf<class ACubeHero> CharacterToSelect);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSelectCharacter(TSubclassOf<class ACubeHero> CharacterToSelect);
	UFUNCTION()
		void OnRep_CharacterSelected();
};
