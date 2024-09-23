// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ActionRPGTypes/ActionRPGEnumTypes.h"
#include "BaseGameplayAbility.generated.h"

class UCombatComponent;
class UActionRPGAbilitySystemComponent;
/**
 * EAbilityActivationPolicy
 * 능력 발동 정책을 정의하는 열거형 클래스
 * - EAP_OnTriggered: 능력이 특정 이벤트에 의해 발동
 * - EAP_OnGiven: 능력이 부여되는 즉시 발동
 */
UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	EAP_OnTriggered,
	EAP_OnGiven
};
/**
 * UBaseGameplayAbility
 * 능력 부여 및 종료 시 커스텀 로직을 처리하는 기본 클래스
 */
UCLASS()
class ACTIONRPGPROJECT_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	/**
	 * UGameplayAbility 클래스에서 능력이 부여될 때 호출되는 메소드.
	 * 능력이 부여될 때 추가 로직을 처리하기 위해 오버라이드.
	 *
	 * @param ActorInfo - 능력이 부여된 액터의 정보
	 * @param Spec - 능력의 구체적인 정보
	 */
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	/**
	 * 능력이 종료될 때 호출되는 메소드.
	 * 능력 종료 시 추가 로직을 처리하기 위해 오버라이드.
	 *
	 * @param Handle - 종료할 능력의 핸들
	 * @param ActorInfo - 능력이 적용된 액터의 정보
	 * @param ActivationInfo - 능력 활성화 정보
	 * @param bReplicateEndAbility - 종료된 능력을 복제할지 여부
	 * @param bWasCancelled - 능력이 취소되었는지 여부
	 */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/**
	 * 타겟 액터에 대해 게임플레이 효과를 적용하는 메소드.
	 *
	 * 이 함수는 특정 액터에게 주어진 게임플레이 효과 스펙 핸들을 직접 적용하며,
	 * 성공적으로 효과가 적용되면 FActiveGameplayEffectHandle을 반환.
	 * 이 핸들은 적용된 효과의 참조를 제공하며, 실패 시 유효하지 않은 핸들을 반환.
	 *
	 * @param targetActor - 효과가 적용될 대상 액터
	 * @param inSpecHandle - 적용할 게임플레이 효과의 스펙 핸들
	 * @return FActiveGameplayEffectHandle - 적용된 효과의 핸들, 적용되지 않으면 유효하지 않은 핸들 반환
	 */
	FActiveGameplayEffectHandle ApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& inSpecHandle);
	/**
	 * 블루프린트에서 호출 가능한 메소드로, 지정된 타겟 액터에 게임플레이 효과 스펙 핸들을 적용하는 메소드.
	 *
	 * 이 함수는 ApplyEffectSpecHandleToTarget 메소드의 블루프린트 버전으로,
	 * 게임플레이 효과를 적용할 때 성공 여부를 EActionRPGSuccessType 열거형을 통해 확인 가능.
	 * 결과적으로 게임플레이 효과 적용이 성공적이었는지 상태를 추적하는 데 사용되며,
	 * 성공 시 적용된 FActiveGameplayEffectHandle을 반환.
	 *
	 * @param targetActor - 효과가 적용될 타겟 액터
	 * @param inSpecHandle - 적용할 게임플레이 효과의 스펙 핸들
	 * @param outSuccessType - 적용 성공 여부를 반환하는 변수, EActionRPGSuccessType을 사용하여 상태를 반환
	 *                         (예: 성공, 실패 등의 상태)
	 * @return FActiveGameplayEffectHandle - 적용된 효과의 핸들, 적용되지 않으면 유효하지 않은 핸들 반환
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "outSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& inSpecHandle, EActionRPGSuccessType& outSuccessType);

public: // Getter Setter
	/**
	 * 전투 컴포넌트를 반환하는 메소드.
	 *
	 * @return UCombatComponent* - 전투 컴포넌트 객체
	 */
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UCombatComponent* GetCombatComponent() const;
	/**
	 * 액션 RPG 전용 능력 시스템 컴포넌트를 반환하는 메소드.
	 *
	 * @return UActionRPGAbilitySystemComponent* - 액션 RPG 능력 시스템 컴포넌트 객체
	 */
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UActionRPGAbilitySystemComponent* GetActionRPGAbilitySystemComponent() const;

protected:
	/**
	 * 능력 발동 정책을 결정하는 변수
	 * 기본값은 EAP_OnTriggered로 설정
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityActivationPolicy abilityActivationPolicy_ = EAbilityActivationPolicy::EAP_OnTriggered;
};
