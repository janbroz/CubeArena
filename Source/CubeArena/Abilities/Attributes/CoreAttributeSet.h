// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CoreAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class CUBEARENA_API UCoreAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UCoreAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

public:
	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Health)

	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, MaxHealth)

	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_HealthPerSecond)
		FGameplayAttributeData HealthPerSecond;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, HealthPerSecond)


	// For later
	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_MovementSpeed)
		FGameplayAttributeData MovementSpeed;
	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Strength)
		FGameplayAttributeData Strength;
	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Agility)
		FGameplayAttributeData Agility;
	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Intellect)
		FGameplayAttributeData Intellect;
	UPROPERTY(Category = "Core Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Stamina)
		FGameplayAttributeData Stamina;

protected:
	// Proportionally adjust the attribute according to the max value
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);


	UFUNCTION()
		virtual void OnRep_Health();
	UFUNCTION()
		virtual void OnRep_MaxHealth();
	UFUNCTION()
		virtual void OnRep_HealthPerSecond();
	UFUNCTION()
		virtual void OnRep_MovementSpeed();
	UFUNCTION()
		virtual void OnRep_Strength();
	UFUNCTION()
		virtual void OnRep_Agility();
	UFUNCTION()
		virtual void OnRep_Intellect();
	UFUNCTION()
		virtual void OnRep_Stamina();


};
