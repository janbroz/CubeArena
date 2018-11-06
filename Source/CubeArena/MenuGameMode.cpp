// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"
#include "Player/MenuPlayerController.h"


AMenuGameMode::AMenuGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AMenuPlayerController::StaticClass();
}