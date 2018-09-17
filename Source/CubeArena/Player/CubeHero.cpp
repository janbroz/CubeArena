// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeHero.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACubeHero::ACubeHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 1000.f;
	CameraArm->bDoCollisionTest = false;
	CameraArm->bAbsoluteRotation = true;
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArm->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);


}

// Called when the game starts or when spawned
void ACubeHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubeHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

