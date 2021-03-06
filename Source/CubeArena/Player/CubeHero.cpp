// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeHero.h"
#include "CubeArena.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

FName ACubeHero::AbilitySystemName(TEXT("AbilitySystem"));

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

	// The ability system component.
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(ACubeHero::AbilitySystemName);
	AbilitySystem->SetIsReplicated(true);

	// The attribute set
	AttributeSet = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("AttributeSet"));

	CharacterLevel = 1;
	bAbilitiesInitialized = false;
}

// Called when the game starts or when spawned
void ACubeHero::BeginPlay()
{
	Super::BeginPlay();
	

	//if (AbilitySystem)
	//{
	//	if (HasAuthority() && Ability)
	//	{
	//		AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, 0));
	//	}
	//	AbilitySystem->InitAbilityActorInfo(this, this);

	//	//AbilitySystem.GetOrCreateAttributeSubobject(AttributeSets[0]);

	//	for (TSubclassOf<UAttributeSet>& Set : AttributeSets)
	//	{
	//		AbilitySystem->InitStats(Set, nullptr);
	//	}
	//}
}

void ACubeHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACubeHero, CharacterLevel);
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


	AbilitySystem->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}

void ACubeHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->RefreshAbilityActorInfo();

	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

float ACubeHero::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ACubeHero::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float ACubeHero::GetHealthPerSecond() const
{
	return AttributeSet->GetHealthPerSecond();
}

float ACubeHero::GetStrength() const
{
	return AttributeSet->GetStrength();
}

float ACubeHero::GetStamina() const
{
	return AttributeSet->GetStamina();
}

float ACubeHero::GetAgility() const
{
	return AttributeSet->GetAgility();
}

float ACubeHero::GetIntellect() const
{
	return AttributeSet->GetIntellect();
}

void ACubeHero::AddStartupGameplayAbilities()
{
	check(AbilitySystem);

	if (Role == ROLE_Authority && !bAbilitiesInitialized)
	{
		// Do something here


		// Apply the passives
		for (TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, CharacterLevel, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystem);
			}
		}

		bAbilitiesInitialized = true;
	}
}

void ACubeHero::AquireAbility(TSubclassOf<UGameplayAbility> NewAbility)
{
	if (AbilitySystem)
	{
		if (HasAuthority() && NewAbility)
		{
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = NewAbility;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef, 1);
			AbilitySystem->GiveAbility(AbilitySpec);
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

int32 ACubeHero::GetCharacterLevel() const
{
	return CharacterLevel;
}

bool ACubeHero::SetCharacterLevel(int32 NewLevel)
{
	if (CharacterLevel != NewLevel && NewLevel > 0)
	{
		// Remove abilties;
		CharacterLevel = NewLevel;
		AddStartupGameplayAbilities();

		return true;
	}
	return false;
}

void ACubeHero::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
	}
}