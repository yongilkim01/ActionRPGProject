// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/CombatComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
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

	// 무기가 목표를 맞출 때 호출되는 델리게이트와 메소드를 바인딩
	RegistWeapon->onWeaponHitTarget_.BindUObject(this, &ThisClass::OnHitTargetActor);
	// 무기로부터 목표와의 접촉이 종료될 때 호출되는 델리게이트와 메소드를 바인딩
	RegistWeapon->onWeaponPulledFromTarget_.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	// 장착을 한것인지를 검사
	if (bEquip)
	{
		// 현재 장착중인 Weapon tag에 등록하려는 Weapon tag를 할당
		currentEquippedWeaponTag_ = RegistWeaponTag;
	}
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

	// 멤버 메소드를 사용하여 현재 장착중인 BaseWeapon 객체를 반환
	return GetCharacterWeaponByTag(currentEquippedWeaponTag_);
}

void UCombatComponent::ToggleWeaponCollision(bool inIsShouldEnable, EToggleDamageType inToggleDamageType)
{
	// 만약 ToggleDamageType이 현재 장착된 무기(ETD_CurrentEquippedWeapon)라면
	if (inToggleDamageType == EToggleDamageType::ETD_CurrentEquippedWeappon)
	{
		// 현재 장착된 무기를 가져옴
		ABaseWeapon* weaponToToggle = GetCurrentEquippedWeapon();

		// 무기가 유효한지 확인
		check(weaponToToggle);

		// 무기 충돌을 활성화할지 비활성화할지 여부에 따라 충돌 설정을 변경
		if (inIsShouldEnable)
		{
			// 충돌을 활성화(QueryOnly)하고 디버그 메시지 출력
			weaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			// 충돌을 비활성화(NoCollision)하고 디버그 메시지 출력
			weaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			// 비활성화 하면서 콜리전 도중 추가된 액터들의 배열을 초기화
			overlappedActors_.Empty();
		}
	}

	// TODO: 바디 콜리전 박스 처리 기능 추가
}

void UCombatComponent::OnHitTargetActor(AActor* inHitActor)
{
}

void UCombatComponent::OnWeaponPulledFromTargetActor(AActor* inInteractedActor)
{
}
