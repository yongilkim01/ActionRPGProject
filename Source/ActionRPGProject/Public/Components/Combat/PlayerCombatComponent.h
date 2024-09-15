// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/CombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class APlayerWeapon;

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UPlayerCombatComponent : public UCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	APlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag weaponTag_) const;
};
