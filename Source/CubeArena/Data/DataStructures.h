// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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

// For the ability system
UENUM(BlueprintType)
enum class AbilityInput : uint8 
{
	UseAbility1		UMETA(DisplayName = "Use Spell 1"),
	UseAbility2		UMETA(DisplayName = "Use Spell 2"),
	UseAbility3		UMETA(DisplayName = "Use Spell 3"),
	UseAbility4		UMETA(DisplayName = "Use Spell 4"),
};


// Defines the class our player is using. Gives different bonuses for the attributes
// according to his class.
UENUM(BlueprintType)
enum class EHeroClass : uint8
{
	Warrior			UMETA(DisplayName = "Warrior"),
	Caster			UMETA(DisplayName = "Caster"),
	Ranger			UMETA(DisplayName = "Ranger"),
	Assassin		UMETA(DisplayName = "Assassin")
};

UENUM(BlueprintType)
enum class EStatName : uint8
{
	Strength		UMETA(DisplayName = "Strength"),
	Agility			UMETA(DisplayName = "Agility"),
	Intellect		UMETA(DisplayName = "Intellect"),
	Stamina			UMETA(DisplayName = "Stamina")
};

USTRUCT(Blueprintable)
struct FClassInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	FClassInformation()
		: ClassName()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeroTable)
		FString ClassName;
};



class CUBEARENA_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
