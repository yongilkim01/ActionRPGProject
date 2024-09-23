// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/PlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ActionRPGGameplayTags.h"

#include "ActionRPGDebugHelper.h"

/**
 * 플레이어가 소지한 무기 중 지정된 태그에 해당하는 무기를 반환하는 메소드
 *
 * @param weaponTag - 찾고자 하는 무기의 태그
 * @return APlayerWeapon* - 태그에 해당하는 무기 객체
 */
APlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag weaponTag) const
{
    return Cast<APlayerWeapon>(GetCharacterWeaponByTag(weaponTag));
}

/**
 * 플레이어가 현재 장착하고 있는 무기를 반환하는 메소드
 *
 * @return APlayerWeapon* - 현재 장착 중인 무기 객체
 */
APlayerWeapon* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<APlayerWeapon>(GetCurrentEquippedWeapon());
}

/**
 * 플레이어가 현재 장착한 무기의 지정된 레벨에 따른 피해량을 반환하는 메소드
 *
 * @param inLevel - 무기의 레벨
 * @return float - 입력된 레벨에 따른 무기의 피해량
 */
float UPlayerCombatComponent::GetPlayerCurrentEquipWeaponDamageAtLevel(float inLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->playerWeaponData_.weaponBaseDamage_.GetValueAtLevel(inLevel);
}

/**
 * 플레이어가 적을 타격했을 때 호출되는 메소드
 *
 * @param inHitActor - 플레이어가 타격한 대상 액터
 */
void UPlayerCombatComponent::OnHitTargetActor(AActor* inHitActor)
{
    // 이미 타격한 액터가 목록에 있는지 확인하고, 있으면 중복 타격을 방지
    if (overlappedActors_.Contains(inHitActor))
    {
        return;
    }

    // 타격한 액터를 목록에 추가
    overlappedActors_.AddUnique(inHitActor);

    // 게임플레이 이벤트 데이터를 설정하고 적을 타격했음을 알림
    FGameplayEventData gameplayEventData;
    gameplayEventData.Instigator = GetOwnerPawn();
    gameplayEventData.Target = inHitActor;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwnerPawn(),
        ActionRPGGameplayTags::Shared_Event_MeleeHit,
        gameplayEventData
    );
}

/**
 * 무기를 적으로부터 뽑아낼 때 호출되는 메소드
 *
 * @param inInteractedActor - 상호작용한 액터 (적)
 */
void UPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* inInteractedActor)
{
    // 무기를 뽑은 액터의 이름과 함께 디버그 메시지를 출력
    Debug::PrintDebugMessage(GetOwnerPawn()->GetActorNameOrLabel() + TEXT(" weapon pulled ") + inInteractedActor->GetActorNameOrLabel(), FColor::Red);
}
