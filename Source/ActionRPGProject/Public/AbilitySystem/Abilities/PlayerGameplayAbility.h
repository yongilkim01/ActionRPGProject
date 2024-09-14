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
	// PlayerCharacter 객체의 약한 포인터
	TWeakObjectPtr<APlayerCharacter> weakPlayerCharacter_;
	
	// ActionRPGPlayerController 객체의 약한 포인터
	TWeakObjectPtr<AActionRPGPlayerController> weakPlayerController_;

	// PlayerCombatComponent 객체의 약한 포인터
	TWeakObjectPtr<UPlayerCombatComponent> weakPlayerCombatComponent_;

public:
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	APlayerCharacter* GetPlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	AActionRPGPlayerController* GetPlayerController();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponent();
};