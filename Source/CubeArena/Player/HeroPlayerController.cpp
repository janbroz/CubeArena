// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroPlayerController.h"
#include "Player/CubeHero.h"
#include "UObject/ConstructorHelpers.h"
#include "AbilitySystemComponent.h"
#include "Widgets/PlayerHUD/HeroHUDWidget.h"

AHeroPlayerController::AHeroPlayerController() 
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> HeroHUD_BP(TEXT("/Game/UI/PlayerHUD/HeroHUD_BP.HeroHUD_BP_C"));
	if (HeroHUD_BP.Object)
	{
		HUDWidgetClass = HeroHUD_BP.Object;
	}
}

void AHeroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AHeroPlayerController::Jump);
	InputComponent->BindAction("LeftMouseButton", EInputEvent::IE_Pressed, this, &AHeroPlayerController::LeftMouseButton);
	InputComponent->BindAction("RightMouseButton", EInputEvent::IE_Pressed, this, &AHeroPlayerController::RightMouseButton);

	InputComponent->BindAxis("HorizontalMovement", this, &AHeroPlayerController::HorizontalMovement);
	InputComponent->BindAxis("VerticalMovement", this, &AHeroPlayerController::VerticalMovement);

	/*ACubeHero* Hero = Cast<ACubeHero>(GetPawn());
	if (Hero)
	{
		Hero->AbilitySystem->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
	}*/
}

void AHeroPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLocalMouseLoc();
}

void AHeroPlayerController::VerticalMovement(float Amount)
{
	if (GetCharacter() && Amount != 0.f)
	{
		ACharacter* Hero = GetCharacter();
		if (Hero)
		{
			Hero->AddMovementInput(FVector::ForwardVector, Amount);
		}
	}
}

void AHeroPlayerController::HorizontalMovement(float Amount)
{
	if (GetCharacter() && Amount != 0.f)
	{
		ACharacter* Hero = GetCharacter();
		if (Hero)
		{
			Hero->AddMovementInput(FVector::RightVector, Amount);
		}
	}
}

void AHeroPlayerController::UpdateLocalMouseLoc()
{
	if (IsLocalController())
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		if (Hit.bBlockingHit)
		{
			AlignHeroToMouseLoc(Hit.Location);
		}
	}
}

void AHeroPlayerController::AlignHeroToMouseLoc(FVector MouseLoc)
{
	if (GetCharacter())
	{
		FVector HeroLocation = GetCharacter()->GetActorLocation();
		FRotator LookAtRot = (MouseLoc - HeroLocation).Rotation();
		FRotator HeroRot = GetControlRotation();
		HeroRot.Yaw = LookAtRot.Yaw;
		SetControlRotation(HeroRot);

		if (Role < ROLE_Authority)
		{
			Server_AlignHeroToMouseLoc(MouseLoc);
		}
	}
}

void AHeroPlayerController::Server_AlignHeroToMouseLoc_Implementation(FVector MouseLoc)
{
	AlignHeroToMouseLoc(MouseLoc);
}

bool AHeroPlayerController::Server_AlignHeroToMouseLoc_Validate(FVector MouseLoc)
{
	return true;
}

void AHeroPlayerController::LeftMouseButton()
{

}

void AHeroPlayerController::RightMouseButton()
{

}

void AHeroPlayerController::Jump()
{
	ACharacter* Hero = GetCharacter();
	if (Hero)
	{
		Hero->Jump();
	}
}

void AHeroPlayerController::Possess(APawn* NewPawn)
{
	Super::Possess(NewPawn);

	if (NewPawn)
	{
		// Notify stuff

		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UHeroHUDWidget>(this, HUDWidgetClass);
			if (HUDWidget)
			{
				HUDWidget->AddToViewport();
			}
		}
	}
}

void AHeroPlayerController::UnPossess()
{
	Super::UnPossess();
}