// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "Controllers/ActionRPGPlayerController.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "ActionRPGGameplayTags.h"

/**
 * 플레이어의 공격 피해에 대한 게임플레이 효과를 생성하는 메소드
 *
 * @param effectClass - 생성할 게임플레이 효과 클래스
 * @param inWeaponBaseDamage - 무기의 기본 피해량
 * @param inCurrentAttackTypeTag - 현재 공격 유형의 태그
 * @param inUsedComboCount - 현재 콤보 카운트
 * @return FGameplayEffectSpecHandle - 생성된 게임플레이 효과 스펙 핸들
 */
FGameplayEffectSpecHandle UPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> effectClass, float inWeaponBaseDamage, FGameplayTag inCurrentAttackTypeTag, int32 inUsedComboCount)
{
    check(effectClass);  // UGameplayEffect 클래스가 유효한지 확인

    // FGameplayEffectContextHandle을 생성하고 필요한 정보 설정
    FGameplayEffectContextHandle contextHandle = GetActionRPGAbilitySystemComponent()->MakeEffectContext();
    contextHandle.SetAbility(this);
    contextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    contextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    // FGameplayEffectSpecHandle을 생성, 레벨과 컨텍스트를 기반으로 설정
    FGameplayEffectSpecHandle effectSpecHandle = GetActionRPGAbilitySystemComponent()->MakeOutgoingSpec(
        effectClass,
        GetAbilityLevel(),
        contextHandle
    );

    // 기본 피해량을 SetByCaller로 설정
    effectSpecHandle.Data->SetSetByCallerMagnitude(
        ActionRPGGameplayTags::Shared_SetByCaller_BaseDamage,
        inWeaponBaseDamage
    );

    // 공격 유형 태그가 유효할 경우 해당 태그로 콤보 카운트 설정
    if (inCurrentAttackTypeTag.IsValid())
    {
        effectSpecHandle.Data->SetSetByCallerMagnitude(inCurrentAttackTypeTag, inUsedComboCount);
    }

    return effectSpecHandle;  // 생성된 FGameplayEffectSpecHandle 반환
}

/**
 * 플레이어 캐릭터 객체를 반환하는 함수
 *
 * @return APlayerCharacter* - 플레이어 캐릭터 객체
 */
APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacter()
{
    // Player character 객체의 약한 포인터가 유효하지 않을 경우 
    // 타입 캐스트 후 CurrentActorInfo의 AvatarActor로부터 플레이어 캐릭터를 가져와 할당
    if (!weakPlayerCharacter_.IsValid())
    {
        weakPlayerCharacter_ = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
    }

    // 약한 포인터가 유효한지 확인하고, 유효하면 객체를 반환, 그렇지 않으면 nullptr 반환
    return weakPlayerCharacter_.IsValid() ? weakPlayerCharacter_.Get() : nullptr;
}

/**
 * 액터 정보에서 플레이어 컨트롤러 객체를 반환하는 함수
 *
 * @return AActionRPGPlayerController* - 플레이어 컨트롤러 객체
 */
AActionRPGPlayerController* UPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
    // Player controller 객체의 약한 포인터가 유효하지 않을 경우
    // 타입 캐스트 후 CurrentActorInfo의 PlayerController에서 플레이어 컨트롤러를 가져와 할당
    if (!weakPlayerController_.IsValid())
    {
        weakPlayerController_ = Cast<AActionRPGPlayerController>(CurrentActorInfo->PlayerController);
    }

    // 약한 포인터가 유효한지 확인하고, 유효하면 객체를 반환, 그렇지 않으면 nullptr 반환
    return weakPlayerController_.IsValid() ? weakPlayerController_.Get() : nullptr;
}

/**
 * 플레이어 전투 컴포넌트를 반환하는 함수
 *
 * @return UPlayerCombatComponent* - 플레이어 전투 컴포넌트 객체
 */
UPlayerCombatComponent* UPlayerGameplayAbility::GetPlayerCombatComponent()
{
    // 플레이어 캐릭터 객체로부터 전투 컴포넌트를 가져와 반환
    return GetPlayerCharacter()->GetPlayerCombatComponent();
}