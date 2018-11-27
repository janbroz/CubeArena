// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BasicDamageEffectExecCalculation.generated.h"

/**
 * 
 */
UCLASS()
class CUBEARENA_API UBasicDamageEffectExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UBasicDamageEffectExecCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
	
};
