// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseStartUpDataAsset.generated.h"

class UBaseGameplayAbility;
class UActionRPGAbilitySystemComponent;
class UGameplayEffect;

/**
 * UBaseStartUpDataAsset 클래스
 * 게임 시작 시 필요한 능력(Abilities)과 효과(Effects)들을 정의하고 관리하는 데이터 자산 클래스.
 */
UCLASS()
class ACTIONRPGPROJECT_API UBaseStartUpDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * AbilitySystemComponent에 능력을 적용하는 메소드
	 * ASC: 능력 시스템 컴포넌트
	 * ApplyLevel: 적용할 능력의 레벨 (기본값: 1)
	 */
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* ASC, int32 ApplyLevel = 1);

protected:
	/**
	 * 능력 시스템 컴포넌트에 주어진 능력 배열을 적용하는 메소드
	 * InAbilitiesToGive: 부여할 능력들의 배열
	 * InASCToGive: 능력을 적용할 능력 시스템 컴포넌트
	 * ApplyLevel: 적용할 능력의 레벨 (기본값: 1)
	 */
	void GrantAbilities(const TArray< TSubclassOf < UBaseGameplayAbility > >& InAbilitiesToGive, UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	// 시작 시 부여될 게임플레이 능력들의 배열 (게임 시작 시 캐릭터에 적용)
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UBaseGameplayAbility > > startUpGameplayAbilities_;

	// 반응형 능력들의 배열 (특정 조건에서 트리거될 능력들)
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UBaseGameplayAbility > > reactiveAbilities_;

	// 시작 시 적용될 게임플레이 효과들의 배열 (버프나 디버프 같은 효과들)
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf <UGameplayEffect> > startUpGameplayEffects_;

};
