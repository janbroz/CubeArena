// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMenuLocation : uint8
{
	MainMenu		UMETA(DisplayName = "MainMenu"),
	HostingOptions  UMETA(DisplayName = "HostingOptions"),
	ServerFinder	UMETA(DisplayName = "ServerFinder"),
	GameSetup		UMETA(DisplayName = "GameSetup"),
	Options			UMETA(DisplayName = "Options")
};

UENUM(BlueprintType)
enum class EPlayerLocation : uint8
{
	MainMenu		UMETA(DisplayName = "MainMenu"),
	Lobby			UMETA(DisplayName = "Lobby"),
	Game			UMETA(DisplayValue = "Game")
};

class CUBEARENA_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
