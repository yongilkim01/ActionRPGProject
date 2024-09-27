// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "ActionRPGAttributeSet.generated.h"

/**
* 게임플레이 속성 접근자를 정의하는 매크로
* ClassName: 속성이 정의된 클래스의 이름
* PropertyName: 접근할 속성의 이름
* 이 매크로는 4가지 함수(속성의 Getter, Value Getter, Value Setter, Value Init)를 자동으로 생성함
*/
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * UActionRPGAttributeSet 클래스: 캐릭터의 속성을 정의하는 클래스, UAttributeSet을 상속받음
 * 게임플레이에서 사용되는 다양한 속성(체력, 분노, 공격력 등)을 정의
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UActionRPGAttributeSet();

	/**
	 * Gameplay Effect가 속성에 적용된 후 자동으로 호출.
	 * 주로 게임 내 속성(예: 체력, 방어력, 공격력 등)에 변화가 생겼을 때, 그 변화를 처리하는 로직을 구현.
	 * 예를 들어, 데미지를 받았을 때 체력을 감소시키거나, 체력이 0이 되었을 때 캐릭터의 사망 처리.
	 *
	 * FGameplayEffectModCallbackData는 효과가 발생할 때 전달되는 데이터로,
	 * 여기에는 효과를 발생시킨 원인(공격자, 아이템 등)과 영향을 받는 속성에 대한 정보가 포함.
	 *
	 * @param data FGameplayEffectModCallbackData 구조체로 전달되는 효과 발생 데이터.
	 *             이 데이터에는 효과를 발생시킨 대상, 속성 변동의 원인, 속성 값의 변화를 추적하는 정보 등이 포함.
	 */
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& data) override;
public:
	//현재 체력 (읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData currentHealth_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, currentHealth_)

	// 최대 체력(읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData maxHealth_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, maxHealth_)

	// 현재 분노 게이지 (읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData currentRage_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, currentRage_)

	// 최대 분노 게이지 (읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData maxRage_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, maxRage_)

	// 공격력 (읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData attackPower_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, attackPower_)

	// 방어력 (읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData defensePower_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, defensePower_)

	// 방어력 (읽기 전용 속성, 블루프린트에서 사용 가능)
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData damageTaken_;
	ATTRIBUTE_ACCESSORS(UActionRPGAttributeSet, damageTaken_)

};
