// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/PlayerWeapon.h"

APlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag weaponTag_) const
{
    return Cast<APlayerWeapon>(GetCharacterWeaponByTag(weaponTag_));
}
