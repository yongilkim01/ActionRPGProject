// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEExecCalc/GEExecCalcDamageTaken.h"
#include "AbilitySystem/ActionRPGAttributeSet.h"
#include "ActionRPGGameplayTags.h"

#include "ActionRPGDebugHelper.h"

// FActionRPGDamageCapture 구조체: 공격력, 방어력, 입은 피해량을 캡처하는 구조체로, 
// 각 값은 UGameplayEffect가 실행될 때 소스와 타겟의 능력치 데이터를 바탕으로 계산됨.
struct FActionRPGDamageCapture
{
	/**
	* 공격력 속성을 캡처하기 위한 매크로 선언.
	* DECLARE_ATTRIBUTE_CAPTUREDEF는 Unreal Engine의 능력치 시스템(Ability System)에서 특정 FGameplayAttributeData를 캡처하도록 설정.
	* attackPower_는 FGameplayAttributeData 타입으로 선언되어, 능력치(attackPower_) 데이터를 소스(능력 발동자)에서 가져옴.
	* 이 값은 UGameplayEffect에서 공격력이 필요할 때 사용됨.
	*/
	DECLARE_ATTRIBUTE_CAPTUREDEF(attackPower_);

	/**
	* 방어력 속성을 캡처하기 위한 매크로 선언.
	* defensePower_ 역시 FGameplayAttributeData 타입으로 선언되며, 방어력 데이터는 타겟(능력 대상자)에서 가져옴.
	* UGameplayEffect가 실행될 때 타겟의 방어력을 캡처하여 능력의 결과(피해량 감소 등)에 반영됨.
	*/
	DECLARE_ATTRIBUTE_CAPTUREDEF(defensePower_);

	/**
	* 입은 피해량을 기록하기 위한 속성 캡처 매크로.
	* damageTaken_도 FGameplayAttributeData 타입으로 선언되며, 최종 피해량을 기록하기 위해 타겟에서 캡처됨.
	* 이 값은 UGameplayEffect 실행 후 타겟이 받는 최종 피해량에 반영됨.
	*/
	DECLARE_ATTRIBUTE_CAPTUREDEF(damageTaken_);

	// FActionRPGDamageCapture 생성자에서 각 속성에 대한 캡처 정의를 초기화.
	FActionRPGDamageCapture()
	{
		/**
		* 공격력 속성 캡처 정의. 공격력(attackPower_)은 능력의 소스(즉, 공격자)로부터 캡처됨.
		* 캡처된 값은 능력 사용 시 소스의 공격력을 기준으로 계산됨.
		* 여기서 UActionRPGAttributeSet 클래스의 attackPower_ 속성을 가져옴.
		*/
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionRPGAttributeSet, attackPower_, Source, false);

		/**
		* 방어력 속성 캡처 정의. 방어력(defensePower_)은 능력의 타겟(즉, 피해자)에서 캡처됨.
		* 이 값은 타겟의 방어력을 기준으로 피해량 감소나 무효화를 계산하는 데 사용됨.
		* UActionRPGAttributeSet 클래스의 defensePower_ 속성을 가져와 적용.
		*/
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionRPGAttributeSet, defensePower_, Target, false);

		/**
		* 피해량 속성 캡처 정의. damageTaken_은 최종적으로 타겟이 입은 피해량을 기록하는 데 사용됨.
		* 이 속성은 능력이 적용된 후 피해량이 어떻게 변했는지를 계산하는 데 사용되며,
		* 타겟의 피해 속성에 값을 반영함.
		* UActionRPGAttributeSet 클래스의 damageTaken_ 속성을 사용.
		*/
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionRPGAttributeSet, damageTaken_, Target, false);
	}
};

// 캡처된 속성 데이터를 정적으로 반환하는 메소드. 게임 실행 중 한 번만 초기화되고 이후로는 계속해서 동일한 인스턴스를 반환.
static const FActionRPGDamageCapture& GetActionRPGDmageCapture()
{
	// 정적으로 FActionRPGDamageCapture 인스턴스를 생성해, 이를 반환함.
	static FActionRPGDamageCapture actionRPGDamageCapture;
	return actionRPGDamageCapture;
}

// UGEExecCalcDamageTaken 생성자: 게임플레이 효과를 실행할 때 필요한 속성들을 설정.
UGEExecCalcDamageTaken::UGEExecCalcDamageTaken()
{
	/*Slow way of doing capture*/
	/*
	FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
		UWarriorAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
	);
	FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
		AttackPowerProperty,
		EGameplayEffectAttributeCaptureSource::Source,
		false
	);
	*/

	/**
	* 공격력 속성을 캡처 목록에 추가.
	* RelevantAttributesToCapture는 이 효과에서 필요한 속성들을 저장하며, 여기서는 소스의 공격력 속성을 저장.
	*/
	RelevantAttributesToCapture.Add(GetActionRPGDmageCapture().attackPower_Def);

	/**
	* 방어력 속성을 캡처 목록에 추가.
	* 이 효과에서 타겟의 방어력 속성을 캡처하여, 나중에 피해량 계산에 사용됨.
	*/
	RelevantAttributesToCapture.Add(GetActionRPGDmageCapture().defensePower_Def);

	/**
	* 피해량 속성을 캡처 목록에 추가.
	* 타겟이 입은 최종 피해량을 계산하고 기록하기 위해 damageTaken_ 속성을 캡처함.
	*/
	RelevantAttributesToCapture.Add(GetActionRPGDmageCapture().damageTaken_Def);
}

// 능력 실행 시 호출되는 메소드로, 능력 효과가 발동될 때 캡처된 속성들을 기반으로 피해량을 계산하는 메소드.
// 이 메소드는 Unreal Engine의 Ability System에서 UGameplayEffect가 실행될 때 커스텀 로직을 통해
// 피해 계산이나 다른 커스텀 효과를 적용하는 데 사용됨.
void UGEExecCalcDamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    // EffectSpec: 현재 발동 중인 GameplayEffect의 사양을 가져옴.
    // 이 값은 능력 또는 효과에 대한 모든 데이터(속성, 태그, SetByCaller 값 등)를 담고 있음.
    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    // 캡처된 데이터를 평가하는데 필요한 파라미터 설정.
    // AggregatorEvaluateParameters는 소스와 타겟의 태그 정보를 포함해, 캡처된 속성을 평가하는 데 사용됨.
    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();  // 소스의 태그들을 가져옴.
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();  // 타겟의 태그들을 가져옴.

    // 소스의 공격력 값을 캡처된 attackPower_ 속성에서 가져옴.
    // AttemptCalculateCapturedAttributeMagnitude는 캡처된 속성에서 실시간으로 평가된 속성 값을 가져옴.
    // 이 경우에는 소스의 attackPower_Def(공격력)를 평가하고, SourceAttackPower에 저장함.
    float SourceAttackPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetActionRPGDmageCapture().attackPower_Def, EvaluateParameters, SourceAttackPower);
    Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower); // 캡처된 소스 공격력 디버그 출력.

    // SetByCaller 방식으로 전달된 값 중 기본 피해량(BaseDamage)을 초기화.
    // GameplayEffect를 적용할 때, 개발자가 특정 피해량이나 값들을 직접 SetByCaller로 지정할 수 있음.
    // 여기서 BaseDamage는 능력 발동 시 외부에서 설정된 기본 피해량.
    float BaseDamage = 0.f;
    int32 UsedLightAttckComboCount = 0;  // 연속된 가벼운 공격 횟수를 저장할 변수.
    int32 UsedHeavyAttackComboCount = 0; // 연속된 강한 공격 횟수를 저장할 변수.

    // EffectSpec에 포함된 SetByCaller 태그 값들을 순회하며 필요한 값을 추출.
    // 이 과정에서 BaseDamage와 콤보 횟수를 가져옴.
    for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
    {
        // SetByCaller 태그 중 BaseDamage와 정확히 일치하는 태그가 있는지 확인하고 값을 설정.
        if (TagMagnitude.Key.MatchesTagExact(ActionRPGGameplayTags::Shared_SetByCaller_BaseDamage))
        {
            BaseDamage = TagMagnitude.Value;  // BaseDamage를 설정.
            Debug::Print(TEXT("BaseDamage"), BaseDamage); // 캡처된 BaseDamage 디버그 출력.
        }
        // SetByCaller 태그 중 가벼운 공격 콤보 횟수를 설정하는 태그를 찾음.
        if (TagMagnitude.Key.MatchesTagExact(ActionRPGGameplayTags::Player_SetByCaller_AttackType_Light))
        {
            UsedLightAttckComboCount = TagMagnitude.Value;  // 가벼운 공격 콤보 횟수를 설정.
            Debug::Print(TEXT("UsedLightAttckComboCount"), UsedLightAttckComboCount); // 디버그 출력.
        }
        // SetByCaller 태그 중 강한 공격 콤보 횟수를 설정하는 태그를 찾음.
        if (TagMagnitude.Key.MatchesTagExact(ActionRPGGameplayTags::Player_SetByCaller_AttackType_Heavy))
        {
            UsedHeavyAttackComboCount = TagMagnitude.Value;  // 강한 공격 콤보 횟수를 설정.
            Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount); // 디버그 출력.
        }
    }

    // 타겟의 방어력 값을 캡처된 defensePower_ 속성에서 가져옴.
    // 타겟의 방어력 속성을 평가하여 피해 감소 또는 다른 방어 계산을 할 수 있도록 준비함.
    float TargetDefensePower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetActionRPGDmageCapture().defensePower_Def, EvaluateParameters, TargetDefensePower);
    Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower); // 캡처된 타겟 방어력 디버그 출력.

    // 가벼운 공격 콤보가 있을 경우, 콤보 횟수에 따라 피해량을 증가시키는 로직.
    // UsedLightAttckComboCount가 0이 아닐 때 콤보 횟수를 기반으로 피해량을 증가시킴.
    if (UsedLightAttckComboCount != 0)
    {
        // 가벼운 공격 콤보 횟수에 따른 피해 증가 비율 계산 (5%씩 증가).
        const float DamageIncreasePercentLight = (UsedLightAttckComboCount - 1) * 0.05 + 1.f;
        BaseDamage *= DamageIncreasePercentLight; // 기본 피해량에 비율을 곱해 최종 피해량을 갱신.
        Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage); // 수정된 가벼운 공격 피해량 디버그 출력.
    }

    // 강한 공격 콤보가 있을 경우, 콤보 횟수에 따라 피해량을 증가시키는 로직.
    // UsedHeavyAttackComboCount가 0이 아닐 때 강한 공격의 콤보 횟수를 기반으로 피해량을 증가시킴.
    if (UsedHeavyAttackComboCount != 0)
    {
        // 강한 공격 콤보 횟수에 따른 피해 증가 비율 계산 (15%씩 증가).
        const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
        BaseDamage *= DamageIncreasePercentHeavy; // 기본 피해량에 비율을 곱해 최종 피해량을 갱신.
        Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage); // 수정된 강한 공격 피해량 디버그 출력.
    }

    // 최종 피해량 계산: 소스의 공격력과 타겟의 방어력을 기반으로 피해량을 계산.
    // 공격력에 따른 비례 피해량을 방어력으로 나눠, 최종 피해량(FinalDamageDone)을 산출함.
    const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
    Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone); // 최종 피해량 디버그 출력.

    // 최종 피해량이 0보다 크면, 타겟에게 이 피해량을 적용함.
    if (FinalDamageDone > 0.f)
    {
        // 최종 피해량을 적용하기 위한 Modifier를 추가.
        // 이 과정에서 damageTaken_ 속성을 이용해 피해량을 타겟에게 적용함.
        OutExecutionOutput.AddOutputModifier(
            FGameplayModifierEvaluatedData(
                GetActionRPGDmageCapture().damageTaken_Property, // 타겟의 damageTaken_ 속성.
                EGameplayModOp::Override, // 기존 값 덮어쓰기(Override).
                FinalDamageDone // 계산된 최종 피해량을 적용.
            )
        );
    }
}