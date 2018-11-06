// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBEARENA_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct()	override;
	
public:
	UFUNCTION(BlueprintCallable)
		void RefreshSessions();
	UFUNCTION(BlueprintImplementableEvent)
		void BP_RefreshSessions();


};
