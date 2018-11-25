// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Attributes/CoreAttributeSet.h"
#include "CubeHero.generated.h"

class UGameplayEffect;

UCLASS()
class CUBEARENA_API ACubeHero : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACubeHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Ability interface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystem;}

	void PossessedBy(AController* NewController) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
		virtual float GetHealth() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetHealthPerSecond() const;

	UFUNCTION(BlueprintCallable)
		virtual int32 GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable)
		virtual bool SetCharacterLevel(int32 NewLevel);

	// Initial setup of the stats
	void AddStartupGameplayAbilities();

	// Handle att modification
	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);



public:
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class USpringArmComponent* CameraArm;

	// Character level
	UPROPERTY(EditAnywhere, Replicated, Category = Abilities)
		int32 CharacterLevel;
	UPROPERTY()
		int32 bAbilitiesInitialized;

	// This is for the abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TSubclassOf<class UGameplayAbility> Ability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TArray<TSubclassOf<class UAttributeSet>> AttributeSets;
	UPROPERTY()
		UCoreAttributeSet* AttributeSet;

	// This is where the initial stats are overrided
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
		TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;


	static FName AbilitySystemName;

};
