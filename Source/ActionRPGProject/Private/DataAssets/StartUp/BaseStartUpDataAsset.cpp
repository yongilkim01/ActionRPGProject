// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"


void UBaseStartUpDataAsset::GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* inASC, int32 inApplyLevel)
{
	// 인자로 받은 ASC가 유효한지 확인 (inASC가 nullptr일 경우 크래시 발생 방지)
	check(inASC);

	// 시작 시 부여할 능력들 적용
	GrantAbilities(startUpGameplayAbilities_, inASC, inApplyLevel);

	// 반응형 능력들 적용
	GrantAbilities(reactiveAbilities_, inASC, inApplyLevel);

	// 시작 시 적용할 GameplayEffect가 있는지 확인 후 적용
	if (!startUpGameplayEffects_.IsEmpty())
	{
		for (const TSubclassOf < UGameplayEffect >& effectClass : startUpGameplayEffects_)
		{
			// GameplayEffect가 유효한지 확인
			if (!effectClass) continue;

			// 기본 객체(Default Object)를 가져옴
			UGameplayEffect* effectCDO = effectClass->GetDefaultObject<UGameplayEffect>();

			// GameplayEffect를 ASC에 적용
			inASC->ApplyGameplayEffectToSelf(
				effectCDO,					// 적용할 GameplayEffect 객체
				inApplyLevel,				// GameplayEffect 레벨
				inASC->MakeEffectContext()	// GameplayEffect 문맥 생성
			);
		}
	}
}

void UBaseStartUpDataAsset::GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>>& InAbilitiesToGive, UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	// 부여할 GameplayAbility이 비어 있는지 확인
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	// 각 GameplayAbility을 ASC에 부여
	for (const TSubclassOf<UBaseGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		//  GameplayAbility Spec을 설정
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); // GameplayAbility의 소유자 설정
		AbilitySpec.Level = ApplyLevel; // GameplayAbility의 레벨 설정

		// ASC에 GameplayAbility을 부여
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
