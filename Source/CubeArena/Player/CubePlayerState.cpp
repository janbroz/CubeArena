// Fill out your copyright notice in the Description page of Project Settings.

#include "CubePlayerState.h"
#include "Player/CubeHero.h"



ACubePlayerState::ACubePlayerState()
{
	bAlwaysRelevant = true;
}

void ACubePlayerState::SelectCharacter(TSubclassOf<ACubeHero> CharacterToSelect)
{
	if (Role < ROLE_Authority)
	{


	}
	else
	{

	}
}

void ACubePlayerState::ServerSelectCharacter_Implementation(TSubclassOf<ACubeHero> CharacterToSelect)
{


}

bool ACubePlayerState::ServerSelectCharacter_Validate(TSubclassOf<ACubeHero> CharacterToSelect)
{
	return true;
}

void ACubePlayerState::OnRep_CharacterSelected()
{


}