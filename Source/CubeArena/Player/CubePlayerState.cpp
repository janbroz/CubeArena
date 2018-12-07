// Fill out your copyright notice in the Description page of Project Settings.

#include "CubePlayerState.h"
#include "Player/CubeHero.h"
#include "Player/HeroPlayerController.h"
#include "UnrealNetwork.h"

ACubePlayerState::ACubePlayerState()
{
	bAlwaysRelevant = true;
}

void ACubePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACubePlayerState, bHasCharacterSelected);
}

void ACubePlayerState::SelectCharacter(TSubclassOf<ACubeHero> CharacterToSelect)
{
	if (Role < ROLE_Authority)
	{
		ServerSelectCharacter(CharacterToSelect);
	}
	else
	{
		if (!bHasCharacterSelected)
		{
			bHasCharacterSelected = true;
			AHeroPlayerController* PController = Cast<AHeroPlayerController>(GetOwner());
			if (PController)
			{
				AActor* SpawnedHero = GetWorld()->SpawnActor(CharacterToSelect);
				if (SpawnedHero)
				{
					PController->Possess(Cast<APawn>(SpawnedHero));
				}
			}
		}
	}
}

void ACubePlayerState::ServerSelectCharacter_Implementation(TSubclassOf<ACubeHero> CharacterToSelect)
{
	SelectCharacter(CharacterToSelect);
}

bool ACubePlayerState::ServerSelectCharacter_Validate(TSubclassOf<ACubeHero> CharacterToSelect)
{
	return true;
}

void ACubePlayerState::OnRep_CharacterSelected()
{


}