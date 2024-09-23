// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "ActionRPGStructTypes.generated.h"

class UActionRPGLinkedAnimInstance;
class UPlayerGameplayAbility;
class UInputMappingContext;

/**
 * FPlayerAbilitySet
 * 플레이어의 능력 세트를 정의하는 구조체
 * 각 능력 세트는 입력 태그와 해당하는 게임플레이 능력을 포함
 */
USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	/**
	 * 입력 태그, 플레이어가 능력을 사용할 때 매핑되는 태그
	 * 이 태그는 특정 입력에 해당하는 능력을 연결하는 데 사용
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag inputTag_;
	/**
	 * 게임플레이 능력 클래스, 입력 태그와 연관된 실제 능력을 정의
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPlayerGameplayAbility> gameplayAbility_;
	/**
	 * 능력 세트가 유효한지 확인하는 함수
	 *
	 * @return bool - 유효하면 true, 그렇지 않으면 false
	 */
	bool IsValid() const;
};

/**
 * FPlayerWeaponData
 * 플레이어의 무기 데이터를 정의하는 구조체
 * 무기에 따른 애니메이션, 입력 매핑, 능력, 기본 피해량을 포함
 */
USTRUCT(BlueprintType)
struct FPlayerWeaponData
{
	GENERATED_BODY()

	/**
	 * 무기와 연결된 애니메이션 레이어 클래스
	 * 이 레이어는 무기 사용 시 적용될 애니메이션을 정의
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UActionRPGLinkedAnimInstance> weaponLinkedAnimLayer_;
	/**
	 * 무기에 따른 입력 매핑 컨텍스트
	 * 무기 장착 시 해당 무기에 맞는 입력 매핑을 사용
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* weaponInputMappingContext_;
	/**
	 * 무기와 연관된 플레이어 능력 세트
	 * 무기 사용 시 적용될 능력들이 포함된 배열
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> playerWeaponAbilites_;
	/**
	 * 무기의 기본 피해량을 정의하는 ScalableFloat
	 * 레벨이나 상황에 따라 동적으로 변화할 수 있는 무기 피해량
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat weaponBaseDamage_;
};