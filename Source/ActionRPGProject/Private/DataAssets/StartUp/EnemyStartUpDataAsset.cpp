// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/EnemyStartUpDataAsset.h"
#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"

void UEnemyStartUpDataAsset::GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* inASC, int32 inApplyLevel)
{
	// 부모 클래스의 GiveToAbilitySystemComponent 메소드 호출
	Super::GiveToAbilitySystemComponent(inASC, inApplyLevel);

	// 전투 gameplayAbility 배열이 비어 있지 않은 경우
	if (!enemyCombatAbilities_.IsEmpty())
	{
		// enemyCombatAbilities_에 정의된 각 전투 능력 클래스를 순회
		for (const TSubclassOf< UEnemyGameplayAbility >& abilityClass : enemyCombatAbilities_)
		{
			// 능력 클래스가 유효하지 않으면 다음 반복으로 순회
			if (!abilityClass) continue;

			// 능력 사양을 생성하고 소스 객체 및 레벨 설정
			FGameplayAbilitySpec abilitySpec(abilityClass);
			abilitySpec.SourceObject = inASC->GetAvatarActor(); // 소스 객체를 현재 액터로 설정
			abilitySpec.Level = inApplyLevel; // 적용할 레벨 설정

			// 능력을 Ability System Component에 추가
			inASC->GiveAbility(abilitySpec);
		}
	}
}