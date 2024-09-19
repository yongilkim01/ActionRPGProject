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
	// PlayerCharacter ��ü�� ���� ������
	TWeakObjectPtr<APlayerCharacter> weakPlayerCharacter_;
	
	// ActionRPGPlayerController ��ü�� ���� ������
	TWeakObjectPtr<AActionRPGPlayerController> weakPlayerController_;

	// PlayerCombatComponent ��ü�� ���� ������
	TWeakObjectPtr<UPlayerCombatComponent> weakPlayerCombatComponent_;

public:
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	APlayerCharacter* GetPlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	AActionRPGPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponent();
};