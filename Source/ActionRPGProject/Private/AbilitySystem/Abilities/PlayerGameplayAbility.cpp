// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "Controllers/ActionRPGPlayerController.h"
#include "Components/Combat/PlayerCombatComponent.h"

APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacter()
{
    // Player character ��ü�� ���� �����Ͱ� ��ȿ���� ���� ��� �� nullptr�� ��� Ÿ�� ĳ��Ʈ �� �Ҵ�
    if (!weakPlayerCharacter_.IsValid())
    {
        weakPlayerCharacter_ = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
    }
    return weakPlayerCharacter_.IsValid() ? weakPlayerCharacter_.Get() : nullptr;
}

AActionRPGPlayerController* UPlayerGameplayAbility::GetPlayerController()
{
    // Player controller ��ü�� ���� �����Ͱ� ��ȿ���� ���� ��� �� nullptr�� ��� Ÿ�� ĳ��Ʈ �� �Ҵ�
    if (!weakPlayerCharacter_.IsValid())
    {
        weakPlayerController_ = Cast<AActionRPGPlayerController>(CurrentActorInfo->PlayerController);
    }
    return weakPlayerController_.IsValid() ? weakPlayerController_.Get() : nullptr;
}

UPlayerCombatComponent* UPlayerGameplayAbility::GetPlayerCombatComponent()
{
    return GetPlayerCharacter()->GetPlayerCombatComponent();
}
