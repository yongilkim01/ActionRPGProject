// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ActionRPGGameplayAbility.h"


void UBaseStartUpDataAsset::GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(m_ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(m_ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UBaseStartUpDataAsset::GrantAbilities(const TArray<TSubclassOf<UActionRPGGameplayAbility>>& InAbilitiesToGive, UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UActionRPGGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
