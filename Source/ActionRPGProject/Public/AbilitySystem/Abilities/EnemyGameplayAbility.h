// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class AEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UEnemyGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	// 액터 정보에서 적 캐릭터(AEnemyCharacter)를 가져오는 함수, 블루프린트에서 순수 함수로 호출 가능
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorInfo();

	// 액터 정보에서 적 전투 컴포넌트(UEnemyCombatComponent)를 가져오는 함수, 블루프린트에서 순수 함수로 호출 가능
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	// 적 캐릭터에 대한 약한 포인터, 캐릭터 객체를 참조하지만 소유권을 가지지 않음
	TWeakObjectPtr<AEnemyCharacter> weakEnemyCharacter_;
};
