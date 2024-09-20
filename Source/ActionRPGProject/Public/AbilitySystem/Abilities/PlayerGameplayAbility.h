// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "PlayerGameplayAbility.generated.h"

class APlayerCharacter;
class AActionRPGPlayerController;
class UPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UPlayerGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

private:
	// PlayerCharacter 객체의 약한 포인터, 플레이어 캐릭터에 대한 참조를 유지
	TWeakObjectPtr<APlayerCharacter> weakPlayerCharacter_;

	// ActionRPGPlayerController 객체의 약한 포인터, 플레이어 컨트롤러에 대한 참조를 유지
	TWeakObjectPtr<AActionRPGPlayerController> weakPlayerController_;

	// PlayerCombatComponent 객체의 약한 포인터, 플레이어 전투 컴포넌트에 대한 참조를 유지
	TWeakObjectPtr<UPlayerCombatComponent> weakPlayerCombatComponent_;

public:
	// 플레이어 캐릭터를 반환하는 함수, 블루프린트에서 순수 함수로 호출 가능
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	APlayerCharacter* GetPlayerCharacter();

	// 액터 정보에서 플레이어 컨트롤러를 반환하는 함수, 블루프린트에서 순수 함수로 호출 가능
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	AActionRPGPlayerController* GetPlayerControllerFromActorInfo();

	// 플레이어 전투 컴포넌트를 반환하는 함수, 블루프린트에서 순수 함수로 호출 가능
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponent();
};