// Fill out your // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalcDamageTaken.generated.h"

/**
 * UGEExecCalcDamageTaken 
 * UGameplayEffectExecutionCalculation을 상속받아, 공격자가 타겟에게 피해를 입히는 로직을 정의하는 클래스.
 * 이 클래스는 주로 능력치 기반의 계산(예: 공격력, 방어력)을 기반으로 피해량을 결정.
 */
UCLASS()
class ACTIONRPGPROJECT_API UGEExecCalcDamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// 생성자: 실행 중에 필요한 캡처된 속성(Attribute)을 설정.
	UGEExecCalcDamageTaken();

	/**
	 * Execute_Implementation 함수는 실제로 피해량을 계산하는 로직 구현.
	 * @param ExecutionParams - 게임플레이 효과 실행에 필요한 여러 매개변수를 포함.
	 * @param OutExecutionOutput - 실행 결과를 담아 타겟에게 영향을 미치는 출력 데이터.
	 */
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};