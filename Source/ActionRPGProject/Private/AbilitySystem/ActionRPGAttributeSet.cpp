// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionRPGAttributeSet.h"

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
