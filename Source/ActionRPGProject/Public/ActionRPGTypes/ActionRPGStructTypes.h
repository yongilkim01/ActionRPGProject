// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActionRPGStructTypes.generated.h"

class UActionRPGLinkedAnimInstance;

USTRUCT(BlueprintType)
struct FPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UActionRPGLinkedAnimInstance> weaponLinkedAnimLayer_;
};