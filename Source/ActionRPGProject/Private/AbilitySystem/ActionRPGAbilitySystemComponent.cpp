// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"

void UActionRPGAbilitySystemComponent::OnInputAbilityPressed(const FGameplayTag& inputTag)
{
	// ��ǲ �±װ� ��ȿ���� �˻�
	if (!inputTag.IsValid()) return;

	/**
	* GetActivatableAbilities() : ���� Ȱ��ȭ �� �� �ִ� ��� �����Ƽ���� �迭�� ��ȯ
	*/
	for (const FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities())
	{
		// �����Ƽ�� �±��� ��ġ�ϴ� �±װ� �ִ��� �˻�
		if (!abilitySpec.DynamicAbilityTags.HasTagExact(inputTag)) continue;
		
		// �����Ƽ�� Ȱ��ȭ
		TryActivateAbility(abilitySpec.Handle);
	}
}

void UActionRPGAbilitySystemComponent::OnInputAbilityReleased(const FGameplayTag& inputTag)
{
}
