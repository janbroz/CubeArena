// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Engine/World.h"
#include "CubeGameInstance.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UCubeGameInstance* GameInstance = Cast<UCubeGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->Cube_OnUpdateSessionsResultUI.AddDynamic(this, &UMainMenuWidget::RefreshSessions);
	}
}

void UMainMenuWidget::RefreshSessions()
{
	UE_LOG(LogTemp, Warning, TEXT("It should update the sessions"));
	BP_RefreshSessions();
}