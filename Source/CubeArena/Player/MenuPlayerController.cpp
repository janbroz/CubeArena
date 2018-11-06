// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/MainMenu/MainMenuWidget.h"

AMenuPlayerController::AMenuPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> MainMenu_BP(TEXT("/Game/UI/MainMenu/MainMenu_BP.MainMenu_BP_C"));
	if (MainMenu_BP.Object)
	{
		MainMenuWidgetClass = MainMenu_BP.Object;
	}
}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidget && IsLocalController())
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
