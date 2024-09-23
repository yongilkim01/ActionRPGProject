// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalcDamageTaken.h"
#include "AbilitySystem/ActionRPGAttributeSet.h"

struct FActionRPGDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(attackPower_);
	DECLARE_ATTRIBUTE_CAPTUREDEF(defensePower_);

	FActionRPGDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionRPGAttributeSet, attackPower_, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionRPGAttributeSet, defensePower_, Target, false);
	}
};

static const FActionRPGDamageCapture& GetActionRPGDmageCapture()
{
	static FActionRPGDamageCapture actionRPGDamageCapture;
	return actionRPGDamageCapture;
}

UGEExecCalcDamageTaken::UGEExecCalcDamageTaken()
{
	/*Slow way of doing capture*/
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UWarriorAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
	//);
	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);

	RelevantAttributesToCapture.Add(GetActionRPGDmageCapture().attackPower_Def);
	RelevantAttributesToCapture.Add(GetActionRPGDmageCapture().defensePower_Def);
}
