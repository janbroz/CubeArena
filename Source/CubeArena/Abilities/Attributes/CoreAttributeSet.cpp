// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreAttributeSet.h"
#include "CubeArena.h"

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

void UCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

}

void UCoreAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	Super::PostGameplayEffectExecute(Data);

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