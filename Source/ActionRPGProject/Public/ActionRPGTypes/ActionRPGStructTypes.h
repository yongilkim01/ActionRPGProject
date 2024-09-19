// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "ActionRPGStructTypes.generated.h"

class UActionRPGLinkedAnimInstance;
class UPlayerGameplayAbility;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag inputTag_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPlayerGameplayAbility> gameplayAbility_;

	bool IsValid() const;
};


USTRUCT(BlueprintType)
struct FPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UActionRPGLinkedAnimInstance> weaponLinkedAnimLayer_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* weaponInputMappingContext_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> playerWeaponAbilites_;
};