// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreAttributeSet.h"
#include "CubeArena.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Player/CubeHero.h"

UCoreAttributeSet::UCoreAttributeSet()
	: Health(10.f)
	, MaxHealth(10.f)
	, MovementSpeed(1.f)
{
}

void UCoreAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCoreAttributeSet, Health);
	DOREPLIFETIME(UCoreAttributeSet, MaxHealth);
	DOREPLIFETIME(UCoreAttributeSet, MovementSpeed);
}

void UCoreAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Maintain the current max / val percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;
		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}

}

void UCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ACubeHero* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ACubeHero>(TargetActor);
	}


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChanged(0.f, SourceTags);
		}

	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChanged(0.f, SourceTags);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not a valid target to do this"));

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The stat modified is not the health"));
		UE_LOG(LogTemp, Warning, TEXT("This is the att: %s"), *Data.EvaluatedData.Attribute.AttributeName);
	}

}

void UCoreAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCoreAttributeSet, Health);
}

void UCoreAttributeSet::OnRep_MaxHealth()
{

}

void UCoreAttributeSet::OnRep_HealthPerSecond()
{

}