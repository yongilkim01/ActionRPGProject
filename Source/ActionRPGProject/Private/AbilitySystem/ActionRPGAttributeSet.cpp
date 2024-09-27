// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionRPGAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "ActionRPGDebugHelper.h"

UActionRPGAttributeSet::UActionRPGAttributeSet()
{
	// currentHealth_ 초기화: 기본 값 1.0
	InitcurrentHealth_(1.f);
	// maxHealth_ 초기화: 기본 값 1.0
	InitmaxHealth_(1.f);
	// currentRage_ 초기화: 기본 값 1.0
	InitcurrentRage_(1.f);
	// maxRage_ 초기화: 기본 값 1.0
	InitmaxRage_(1.f);
	// attackPower_ 초기화: 기본 값 1.0
	InitattackPower_(1.f);
	// defensePower_ 초기화: 기본 값 1.0
	InitdefensePower_(1.f);
}

void UActionRPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& data)
{
	// 현재 체력(currentHealth_)이 변경된 경우 처리
	if (data.EvaluatedData.Attribute == GetcurrentHealth_Attribute())
	{
		// 체력 값을 0에서 최대 체력 사이로 클램프(clamp)하여 안정성을 보장
		const float newCurrentHealth = FMath::Clamp(GetcurrentHealth_(), 0.f, GetmaxHealth_());
		// 클램프된 새로운 체력 값을 현재 체력(currentHealth_)으로 설정
		SetcurrentHealth_(newCurrentHealth);
	}

	// 현재 분노 게이지(currentRage_)가 변경된 경우 처리
	if (data.EvaluatedData.Attribute == GetcurrentRage_Attribute())
	{
		// 분노 값을 0에서 최대 분노 게이지 사이로 클램프(clamp)하여 안정성을 보장
		const float NewCurrentRage = FMath::Clamp(GetcurrentRage_(), 0.f, GetmaxRage_());
		// 클램프된 새로운 분노 게이지 값을 현재 분노 게이지로 설정
		SetcurrentRage_(NewCurrentRage);
	}

	// 받은 피해량(damageTaken_)이 적용된 경우 처리
	if (data.EvaluatedData.Attribute == GetdamageTaken_Attribute())
	{
		// 기존 체력 값을 저장
		const float OldHealth = GetcurrentHealth_();
		// 받은 피해량을 저장
		const float DamageDone = GetdamageTaken_();
		// 새로운 체력 값 = 기존 체력 - 받은 피해량, 그리고 이를 0과 최대 체력 사이로 클램프
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetmaxHealth_());
		// 클램프된 새로운 체력 값을 현재 체력(currentHealth_)으로 설정
		SetcurrentHealth_(NewCurrentHealth);

		// 디버그 메시지 출력 (기존 체력, 받은 피해량, 새로운 체력 값을 출력)
		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		);
		Debug::PrintDebugMessage(DebugString, FColor::Green);

		// TODO: UI 업데이트 알림 (체력 변경 사항을 UI에 반영하기 위한 처리 필요)
		// TODO: 캐릭터 사망 처리 (체력이 0이 된 경우 캐릭터 사망을 처리할 로직 추가 필요)
		if (NewCurrentHealth == 0.f)
		{
			// 사망 처리 로직을 여기에 구현
		}
	}
}
