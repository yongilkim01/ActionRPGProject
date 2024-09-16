// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionRPGTypes/ActionRPGStructTypes.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

bool FPlayerAbilitySet::IsValid() const
{
	return inputTag_.IsValid() && gameplayAbility_;
}