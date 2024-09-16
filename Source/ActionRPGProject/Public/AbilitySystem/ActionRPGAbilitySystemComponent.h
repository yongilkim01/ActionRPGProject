// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ActionRPGTypes/ActionRPGStructTypes.h"
#include "ActionRPGAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnInputAbilityPressed(const FGameplayTag& inputTag);
	void OnInputAbilityReleased(const FGameplayTag& inputTag);
	
	UFUNCTION(BlueprintCallable, Category = "Character|Ability", meta = (applyLevel = "1"))
	void GrantPlayerWeaponAbilites(const TArray<FPlayerAbilitySet>& weaponAbilites, int32 applyLevel, TArray<FGameplayAbilitySpecHandle>& grantedAbilitySpecHandles);
};
