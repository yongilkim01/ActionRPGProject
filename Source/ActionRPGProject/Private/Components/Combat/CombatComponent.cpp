// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/CombatComponent.h"
#include "Items/Weapons/BaseWeapon.h"

#include "ActionRPGDebugHelper.h"

// GameplayTag�� BaseWeapon�� map ��ü�� ����ϴ� �޼ҵ�
void UCombatComponent::RegisterSpawnedWeapon(FGameplayTag RegistWeaponTag, ABaseWeapon* RegistWeapon, bool bEquip)
{
	// Weapon tag�� ���ؼ� map�� �̹� �߰� �Ǿ� �ִ� tag������ �˻�
	checkf(!characterWeaponMap_.Contains(RegistWeaponTag), TEXT("%s already add in combat component map variable"), *RegistWeaponTag.ToString());
	// BaseWeapon��ü�� ��ȿ���� �˻�
	check(RegistWeapon);

	// map�� �߰�
	characterWeaponMap_.Emplace(RegistWeaponTag, RegistWeapon);

	// ������ �Ѱ������� �˻�
	if (bEquip)
	{
		// ���� �������� Weapon tag�� ����Ϸ��� Weapon tag�� �Ҵ�
		currentEquippedWeaponTag_ = RegistWeaponTag;
	}

	// Debug
	const FString DebugMsg = FString::Printf(TEXT("Weapon name : %s, Weapon tag : %s"), *RegistWeapon->GetName(), *RegistWeaponTag.ToString());
	Debug::PrintDebugMessage(DebugMsg);
}

// GameplayTag�� �ش��ϴ� BaseWeapon��ü�� ��ȯ�ϴ� �޼ҵ�
ABaseWeapon* UCombatComponent::GetCharacterWeaponByTag(FGameplayTag FindWeaponTag) const
{
	// map���� ã�������ϴ� Weapon tag�� �ش��ϴ� BaseWeapon��ü�� �ִ����� �˻�
	if (characterWeaponMap_.Contains(FindWeaponTag))
	{
		// map���� ã������ �ϴ� BaseWeapon��ü�� ������ �ּҸ� ��ȯ
		ABaseWeapon* const* FindWeapon = characterWeaponMap_.Find(FindWeaponTag);
		if (FindWeapon)
		{
			return *FindWeapon;
		}
	}
	return nullptr;
}

// ���� �������� BaseWeapon��ü�� ��ȯ�ϴ� �޼ҵ�
ABaseWeapon* UCombatComponent::GetCurrentEquippedWeapon() const
{
	// ���� �������� Weapon tag�� ��ȿ���� �ʴ´ٸ� nullptr�� ��ȯ
	if (!currentEquippedWeaponTag_.IsValid()) return nullptr;

	// ��� �޼ҵ带 ����Ͽ� BaseWeapon ��ü�� ��ȯ
	return GetCharacterWeaponByTag(currentEquippedWeaponTag_);
}
