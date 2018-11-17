// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/MainMenu/MainMenuWidget.h"
#include "Widgets/Lobby/LobbyWidget.h"
#include "Data/DataStructures.h"
#include "CubeGameInstance.h"

AMenuPlayerController::AMenuPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> MainMenu_BP(TEXT("/Game/UI/MainMenu/MainMenu_BP.MainMenu_BP_C"));
	if (MainMenu_BP.Object)
	{
		MainMenuWidgetClass = MainMenu_BP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> LobbyWidget_BP(TEXT("/Game/UI/Lobby/Lobby_BP.Lobby_BP_C"));
	if (LobbyWidget_BP.Object)
	{
		LobbyWidgetClass = LobbyWidget_BP.Object;
	}
}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UCubeGameInstance* GameInstance = Cast<UCubeGameInstance>(GetGameInstance());
	UE_LOG(LogTemp, Warning, TEXT("It is calling the player controller initialization method"));
	if (GameInstance && MainMenuWidgetClass && LobbyWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid game instance and widgets"));
		if (GameInstance->CurrentLocation == EPlayerLocation::MainMenu)
		{
			UE_LOG(LogTemp, Warning, TEXT("We at the main menu"));

			MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
			if (MainMenuWidget && IsLocalController())
			{
				MainMenuWidget->AddToViewport();

				if (LobbyWidget)
				{
					LobbyWidget->RemoveFromParent();
				}
			}
		}
		if (GameInstance->CurrentLocation == EPlayerLocation::Lobby)
		{
			UE_LOG(LogTemp, Warning, TEXT("We at the lobby"));

			LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
			if (LobbyWidget && IsLocalController())
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("There is a valid lobby widget, but where is the fucking menu widget at?"));
				}

				LobbyWidget->AddToViewport();
				if (MainMenuWidget)
				{
					MainMenuWidget->RemoveFromParent();
				}

			}
		}
	}
}

void AMenuPlayerController::ShowLobby()
{
	if (LobbyWidget)
	{
		LobbyWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
		if (LobbyWidget)
		{
			LobbyWidget->AddToViewport();
		}
	}

	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
