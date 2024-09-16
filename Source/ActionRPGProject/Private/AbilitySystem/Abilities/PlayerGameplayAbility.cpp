// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "Controllers/ActionRPGPlayerController.h"
#include "Components/Combat/PlayerCombatComponent.h"

APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacter()
{
    // Player character 객체의 약한 포인터가 유효하지 않을 경우 즉 nullptr일 경우 타입 캐스트 후 할당
    if (!weakPlayerCharacter_.IsValid())
    {
        weakPlayerCharacter_ = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
    }
    return weakPlayerCharacter_.IsValid() ? weakPlayerCharacter_.Get() : nullptr;
}

AActionRPGPlayerController* UPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
    // Player controller 객체의 약한 포인터가 유효하지 않을 경우 즉 nullptr일 경우 타입 캐스트 후 할당
    if (!weakPlayerController_.IsValid())
    {
        weakPlayerController_ = Cast<AActionRPGPlayerController>(CurrentActorInfo->PlayerController);
    }
    return weakPlayerController_.IsValid() ? weakPlayerController_.Get() : nullptr;
}

UPlayerCombatComponent* UPlayerGameplayAbility::GetPlayerCombatComponent()
{
    return GetPlayerCharacter()->GetPlayerCombatComponent();
}
