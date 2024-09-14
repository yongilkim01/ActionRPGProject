// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/PlayerStartUpDataAsset.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

bool FPlayerAbilitySet::IsValid() const
{
	return inputTag_.IsValid() && gameplayAbility_;
}

void UPlayerStartUpDataAsset::GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* ASC, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(ASC, ApplyLevel);

    for (const FPlayerAbilitySet& AbilitySet : playerAbilitySets_)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.gameplayAbility_);
        AbilitySpec.SourceObject = ASC->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.inputTag_);

        ASC->GiveAbility(AbilitySpec);
    }
}