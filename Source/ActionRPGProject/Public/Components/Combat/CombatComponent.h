// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseActorComponent.h"
#include "GameplayTagContainer.h"
#include "CombatComponent.generated.h"

class ABaseWeapon;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	ETD_CurrentEquippedWeappon,
	ETD_LeftHand,
	ETD_RightHand
};
/**
 * UCombatComponent 클래스
 * 전투 관련 기능을 담당하는 컴포넌트로, 무기의 등록, 조회, 장착 관련 기능을 제공
 */
UCLASS()
class ACTIONRPGPROJECT_API UCombatComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * 무기를 등록하는 메소드
	 * 특정 GameplayTag와 해당 무기(BaseWeapon)를 map에 등록하며, 필요 시 무기를 장착할 수 있음
	 * @param RegistWeaponTag - 등록할 무기의 태그
	 * @param RegistWeapon - 등록할 BaseWeapon 객체
	 * @param bEquip - true일 경우 등록 시 무기를 장착
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag RegistWeaponTag, ABaseWeapon* RegistWeapon, bool bEquip = false);
	/**
	 * 태그를 통해 캐릭터의 무기를 찾는 메소드
	 * 특정 GameplayTag에 해당하는 BaseWeapon 객체를 map에서 검색하여 반환
	 * @param FindWeaponTag - 찾을 무기의 태그
	 * @return BaseWeapon 객체 또는 nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	ABaseWeapon* GetCharacterWeaponByTag(FGameplayTag FindWeaponTag) const;
	/**
	 * 현재 캐릭터가 장착 중인 무기를 반환하는 메소드
	 * 장착 중인 BaseWeapon 객체를 반환
	 * @return 현재 장착 중인 BaseWeapon 객체
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	ABaseWeapon* GetCurrentEquippedWeapon() const;
	/**
	 * 무기 충돌을 활성화하거나 비활성화하는 메소드
	 * 캐릭터가 장착 중인 무기의 충돌 여부를 설정하며, 해당 무기의 공격 여부를 제어
	 * @param inIsShouldEnable - true일 경우 무기 충돌을 활성화, false일 경우 비활성화
	 * @param inToggleDamageType - 적용할 데미지 유형 타입, 기본값은 현재 장착 중인 무기로 설정
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Combat")
	void ToggleWeaponCollision(bool inIsShouldEnable, EToggleDamageType inToggleDamageType = EToggleDamageType::ETD_CurrentEquippedWeappon);
	/**
	 * 주어진 액터와의 충돌이 발생했을 때 호출되는 메소드
	 * 이 메소드는 무기가 목표를 맞출 때 사용되며,
	 * ABaseWeapon::onWeaponHitTarget_ 델리게이트와 연관되어
	 * 해당 액터에 대한 추가적인 처리를 수행.
	 *
	 * @param inHitActor - 충돌한 액터
	 */
	virtual void OnHitTargetActor(AActor* inHitActor);
	/**
	 * 무기로부터 목표 액터가 풀려났을 때 호출되는 메소드
	 * 이 메소드는 무기가 목표와의 접촉을 종료할 때 사용되며,
	 * onWeaponPulledFromTarget_ 델리게이트와 연관되어
	 * 해당 액터에 대한 추가적인 처리를 수행.
	 *
	 * @param inInteractedActor - 접촉이 종료된 액터
	 */
	virtual void OnWeaponPulledFromTargetActor(AActor* inInteractedActor);

public:
	/**
	 * 현재 장착 중인 무기의 태그
	 * 무기의 장착 상태를 나타내는 GameplayTag로 Blueprint에서 읽기 및 쓰기가 가능
	 */
	UPROPERTY(BlueprintReadWrite, Category = "ActionRPG|Combat")
	FGameplayTag currentEquippedWeaponTag_;

protected:
	/**
	 * 콜리전된 액터들의 배열
	 * OnCollision 관련 메소드들에서 사용
	 */
	TArray<AActor*> overlappedActors_;

private:
	/**
	 * 캐릭터가 소유한 무기를 관리하는 map
	 * 무기 태그와 BaseWeapon 객체의 쌍으로 구성된 map 변수로, 캐릭터가 보유한 무기 목록을 관리
	 */
	TMap<FGameplayTag, ABaseWeapon*> characterWeaponMap_;
	
};
