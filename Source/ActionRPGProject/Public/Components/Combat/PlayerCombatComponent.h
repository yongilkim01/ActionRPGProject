// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/CombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class APlayerWeapon;

/**
 * UPlayerCombatComponent
 * UCombatComponent를 상속받은 클래스
 * 플레이어의 전투 관련 기능을 추가하는 컴포넌트
 */
UCLASS()
class ACTIONRPGPROJECT_API UPlayerCombatComponent : public UCombatComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * 주어진 GameplayTag에 해당하는 플레이어가 소지한 무기를 반환하는 메소드.
	 * 
	 * @param weaponTag 찾고자 하는 무기의 GameplayTag
	 * @return 플레이어가 소지한 APlayerWeapon 객체 또는 nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	APlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag weaponTag) const;
	/**
	 * 현재 플레이어가 장비하고 있는 무기를 반환하는 메소드.
	 *
	 * @return 플레이어가 장비한 APlayerWeapon 객체 또는 nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	APlayerWeapon* GetPlayerCurrentEquippedWeapon() const;
	/**
	 * 플레이어가 현재 장착한 무기의 레벨에 따른 피해량을 반환하는 메소드.
	 *
	 * @param inLevel - 무기의 레벨, 해당 레벨에 맞는 피해량을 계산
	 * @return float - 입력된 레벨에 따른 무기의 현재 피해량
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	float GetPlayerCurrentEquipWeaponDamageAtLevel(float inLevel) const;
	/**
	 * 충돌한 목표 액터와의 상호작용을 처리하는 메소드.
	 * @param inHitActor 충돌한 액터
	 */
	virtual void OnHitTargetActor(AActor* inHitActor) override;
	/**
	 * 목표에서 무기가 분리될 때의 상호작용을 처리하는 메소드.
	 * @param inInteractedActor 상호작용한 액터
	 */
	virtual void OnWeaponPulledFromTargetActor(AActor* inInteractedActor) override;
};
