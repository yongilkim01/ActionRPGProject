// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "PlayerGameplayAbility.generated.h"

class APlayerCharacter;
class AActionRPGPlayerController;
class UPlayerCombatComponent;
/**
 * UPlayerGameplayAbility
 * 플레이어 캐릭터의 능력 시스템을 정의하는 클래스
 * UBaseGameplayAbility를 상속받아 사용
 */
UCLASS()
class ACTIONRPGPROJECT_API UPlayerGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	/**
	 * 플레이어의 공격 피해에 대한 효과를 생성하는 메소드
	 *
	 * @param effectClass - 적용할 게임플레이 효과 클래스
	 * @param inWeaponBaseDamage - 무기의 기본 피해량
	 * @param inCurrentAttackTypeTag - 현재 공격 타입 태그
	 * @param inUsedComboCount - 현재 콤보 카운트
	 * @return FGameplayEffectSpecHandle - 생성된 게임플레이 효과 스펙 핸들
	 */
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> effectClass, float inWeaponBaseDamage, FGameplayTag inCurrentAttackTypeTag, int32 inUsedComboCount);

private:
	/**
	 * APlayerCharacter 객체의 약한 포인터
	 * 플레이어 캐릭터에 대한 참조를 유지하되, 메모리 관리를 쉽게 하기 위해 약한 참조를 사용
	 */
	TWeakObjectPtr<APlayerCharacter> weakPlayerCharacter_;

	/**
	 * AActionRPGPlayerController 객체의 약한 포인터
	 * 플레이어 컨트롤러에 대한 참조를 유지
	 */
	TWeakObjectPtr<AActionRPGPlayerController> weakPlayerController_;

	/**
	 * UPlayerCombatComponent 객체의 약한 포인터
	 * 플레이어 전투 컴포넌트에 대한 참조를 유지
	 */
	TWeakObjectPtr<UPlayerCombatComponent> weakPlayerCombatComponent_;

public:
	/**
	 * 플레이어 캐릭터 객체를 반환하는 함수
	 *
	 * @return APlayerCharacter* - 플레이어 캐릭터 객체
	 */
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	APlayerCharacter* GetPlayerCharacter();
	/**
	 * 액터 정보에서 플레이어 컨트롤러 객체를 반환하는 함수
	 *
	 * @return AActionRPGPlayerController* - 플레이어 컨트롤러 객체
	 */
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	AActionRPGPlayerController* GetPlayerControllerFromActorInfo();
	/**
	 * 플레이어 전투 컴포넌트를 반환하는 함수
	 *
	 * @return UPlayerCombatComponent* - 플레이어 전투 컴포넌트 객체
	 */
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponent();
};