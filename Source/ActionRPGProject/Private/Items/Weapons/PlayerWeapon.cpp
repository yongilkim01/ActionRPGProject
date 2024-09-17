// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/PlayerWeapon.h"

void APlayerWeapon::AssignWeaponAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& inSpecHandles)
{
    weaponAbilitySpecHandles_ = inSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> APlayerWeapon::GetWeaponAbilitySpecHandles() const
{
    return weaponAbilitySpecHandles_;
}
