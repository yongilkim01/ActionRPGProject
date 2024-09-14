// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"

void UActionRPGAbilitySystemComponent::OnInputAbilityPressed(const FGameplayTag& inputTag)
{
	// 인풋 태그가 유효한지 검사
	if (!inputTag.IsValid()) return;

	/**
	* GetActivatableAbilities() : 현재 활성화 할 수 있는 모든 어빌리티들의 배열을 반환
	*/
	for (const FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities())
	{
		// 어빌리티의 태그중 일치하는 태그가 있는지 검사
		if (!abilitySpec.DynamicAbilityTags.HasTagExact(inputTag)) continue;
		
		// 어빌리티를 활성화
		TryActivateAbility(abilitySpec.Handle);
	}
}

void UActionRPGAbilitySystemComponent::OnInputAbilityReleased(const FGameplayTag& inputTag)
{
}
