// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "ActionRPGTypes/ActionRPGStructTypes.h"
#include "PlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API APlayerWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FPlayerWeaponData playerWeaponData_;
};
