// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/CombatComponent.h"
#include "Items/Weapons/BaseWeapon.h"

#include "ActionRPGDebugHelper.h"

// GameplayTag와 BaseWeapon을 map 객체에 등록하는 메소드
void UCombatComponent::RegisterSpawnedWeapon(FGameplayTag RegistWeaponTag, ABaseWeapon* RegistWeapon, bool bEquip)
{
	// Weapon tag를 통해서 map에 이미 추가 되어 있는 tag인지를 검사
	checkf(!characterWeaponMap_.Contains(RegistWeaponTag), TEXT("%s already add in combat component map variable"), *RegistWeaponTag.ToString());
	// BaseWeapon객체가 유효한지 검사
	check(RegistWeapon);

	// map에 추가
	characterWeaponMap_.Emplace(RegistWeaponTag, RegistWeapon);

	// 장착을 한것인지를 검사
	if (bEquip)
	{
		// 현재 장착중인 Weapon tag에 등록하려는 Weapon tag를 할당
		currentEquippedWeaponTag_ = RegistWeaponTag;
	}

	// Debug
	const FString DebugMsg = FString::Printf(TEXT("Weapon name : %s, Weapon tag : %s"), *RegistWeapon->GetName(), *RegistWeaponTag.ToString());
	Debug::PrintDebugMessage(DebugMsg);
}

// GameplayTag에 해당하는 BaseWeapon객체를 반환하는 메소드
ABaseWeapon* UCombatComponent::GetCharacterWeaponByTag(FGameplayTag FindWeaponTag) const
{
	// map에서 찾으려고하는 Weapon tag에 해당하는 BaseWeapon객체가 있는지를 검사
	if (characterWeaponMap_.Contains(FindWeaponTag))
	{
		// map에서 찾으려고 하는 BaseWeapon객체의 포인터 주소를 반환
		ABaseWeapon* const* FindWeapon = characterWeaponMap_.Find(FindWeaponTag);
		if (FindWeapon)
		{
			return *FindWeapon;
		}
	}
	return nullptr;
}

// 현재 장착중인 BaseWeapon객체를 반환하는 메소드
ABaseWeapon* UCombatComponent::GetCurrentEquippedWeapon() const
{
	// 현재 장착중인 Weapon tag가 유효하지 않는다면 nullptr을 반환
	if (!currentEquippedWeaponTag_.IsValid()) return nullptr;

	// 멤버 메소드를 사용하여 BaseWeapon 객체를 반환
	return GetCharacterWeaponByTag(currentEquippedWeaponTag_);
}
