// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeArenaGameModeBase.h"
#include "Player/CubeHero.h"
#include "Player/HeroPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACubeArenaGameModeBase::ACubeArenaGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UClass> Hero_Bp(TEXT("/Game/Characters/PrototypeHero/ProtoCube.ProtoCube_C"));
	if (Hero_Bp.Object)
	{
		DefaultPawnClass = Hero_Bp.Object;
	}
	else
	{
		DefaultPawnClass = ACubeHero::StaticClass();
	}

	PlayerControllerClass = AHeroPlayerController::StaticClass();
}