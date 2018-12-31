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
	
	// overriding the possesion
	void PossessedBy(AController* NewController) override;
	void Restart() override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
		virtual float GetHealth() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetHealthPerSecond() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetStrength() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetStamina() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetIntellect() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetAgility() const;
	UFUNCTION(BlueprintCallable)
		virtual int32 GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable)
		virtual bool SetCharacterLevel(int32 NewLevel);

	// Initial setup of the stats
	void AddStartupGameplayAbilities();
	// Gain an ability
	UFUNCTION(BlueprintCallable)
		void AquireAbility(TSubclassOf<UGameplayAbility> NewAbility);

	// Handle att modification
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);


	UFUNCTION(BlueprintImplementableEvent)
		void MainAttack();
	UFUNCTION(BlueprintImplementableEvent)
		void NotifyHitActorsByWeapon(const TArray<AActor*>& HitActors);

	UFUNCTION(BlueprintImplementableEvent)
		void SecondaryAttack();



public:
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class USpringArmComponent* CameraArm;
	UPROPERTY(BlueprintReadWrite, Category = "PlayerInformation")
		class UInventoryComponent* InventoryComponent;

	// Character information
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Class information")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class information")
		FString HeroName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class information")
		FString HeroDetails;


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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCoreAttributeSet* AttributeSet;

	// This is where the initial stats are overrided
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
		TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;


	static FName AbilitySystemName;

public:
	// Experimental UI function
	UFUNCTION()
		void OnHealthChangedFromMulticast(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter", meta = (DisplayName = "OnHealthChanged"))
		void BP_OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION()
		void HeroDie();
	UFUNCTION(BlueprintImplementableEvent)
		void BP_HeroDie();
};
