// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "EnemyStartUpDataAsset.generated.h"

class UEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UEnemyStartUpDataAsset : public UBaseStartUpDataAsset
{
	GENERATED_BODY()
	
public:
	/**
	* Ability System Component에 gameplayAbility을 적용하는 메소드
	* inASC: 적용할 능력 시스템 컴포넌트
	* inApplyLevel: gameplayAbility을 적용할 레벨 (기본값은 1)
	*/
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* inASC, int32 inApplyLevel = 1) override;

private:
	/**
	* 적 전투 gameplayAbility들을 저장하는 배열
	* Blueprint에서 기본값으로 설정 가능하며, "StartUpData" 카테고리로 분류
	*/
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf <UEnemyGameplayAbility> > enemyCombatAbilities_;
};
