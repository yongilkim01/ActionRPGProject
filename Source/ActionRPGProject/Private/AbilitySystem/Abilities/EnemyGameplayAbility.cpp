// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"
#include "Characters/EnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"

// 액터 정보에서 AEnemyCharacter 객체를 가져오는 함수
AEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    // weakEnemyCharacter_가 유효하지 않으면 현재 액터 정보에서 캐스팅하여 설정
    if (!weakEnemyCharacter_.IsValid())
    {
        weakEnemyCharacter_ = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }

    // weakEnemyCharacter_가 유효하면 반환, 그렇지 않으면 nullptr 반환
    return weakEnemyCharacter_.IsValid() ? weakEnemyCharacter_.Get() : nullptr;
}

// 액터 정보에서 UEnemyCombatComponent 객체를 가져오는 함수
UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    // 적 캐릭터에서 적 전투 컴포넌트를 가져와 반환
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}