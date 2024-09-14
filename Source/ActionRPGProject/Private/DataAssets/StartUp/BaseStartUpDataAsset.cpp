// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"


void UBaseStartUpDataAsset::GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(startUpGameplayAbilities_, InASCToGive, ApplyLevel);
	GrantAbilities(reactiveAbilities_, InASCToGive, ApplyLevel);
}

void UBaseStartUpDataAsset::GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>>& InAbilitiesToGive, UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UBaseGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
