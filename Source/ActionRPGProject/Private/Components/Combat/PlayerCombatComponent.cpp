// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/PlayerWeapon.h"
#include "ActionRPGDebugHelper.h"

APlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag weaponTag_) const
{
    return Cast<APlayerWeapon>(GetCharacterWeaponByTag(weaponTag_));
}

void UPlayerCombatComponent::OnHitTargetActor(AActor* inHitActor)
{
    Debug::PrintDebugMessage(GetOwnerPawn()->GetActorNameOrLabel() + TEXT(" hit ") + inHitActor->GetActorNameOrLabel(), FColor::Green);
}

void UPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* inInteractedActor)
{
    Debug::PrintDebugMessage(GetOwnerPawn()->GetActorNameOrLabel() + TEXT(" weapon pulled ") + inInteractedActor->GetActorNameOrLabel(), FColor::Red);
}
