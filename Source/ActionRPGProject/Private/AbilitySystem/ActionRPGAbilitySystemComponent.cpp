// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

void UActionRPGAbilitySystemComponent::OnInputAbilityPressed(const FGameplayTag& inputTag)
{
	// 인풋 태그가 유효한지 검사
	if (!inputTag.IsValid()) return;

	/**
	* GetActivatableAbilities() : 현재 활성화 할 수 있는 모든 어빌리티들의 배열을 반환
	*/
	for (const FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities())
	{
		// 어빌리티의 태그 중 일치하는 태그가 이는지 검사
		if (!abilitySpec.DynamicAbilityTags.HasTagExact(inputTag)) continue;
		
		// 어빌리티를 활성화
		TryActivateAbility(abilitySpec.Handle);
	}
}

void UActionRPGAbilitySystemComponent::OnInputAbilityReleased(const FGameplayTag& inputTag)
{
}

void UActionRPGAbilitySystemComponent::GrantPlayerWeaponAbilites(const TArray<FPlayerAbilitySet>& weaponAbilites, int32 applyLevel, TArray<FGameplayAbilitySpecHandle>& grantedAbilitySpecHandles)
{
	if (weaponAbilites.IsEmpty()) return;

	for (const FPlayerAbilitySet& abilitySet : weaponAbilites)
	{
		if (!abilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec abilitySpec(abilitySet.gameplayAbility_);
		abilitySpec.SourceObject = GetAvatarActor();
		abilitySpec.Level = applyLevel;
		abilitySpec.DynamicAbilityTags.AddTag(abilitySet.inputTag_);

		grantedAbilitySpecHandles.AddUnique(GiveAbility(abilitySpec));
	}
}
