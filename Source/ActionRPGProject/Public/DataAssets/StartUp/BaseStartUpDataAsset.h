// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseStartUpDataAsset.generated.h"

class UBaseGameplayAbility;
class UActionRPGAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UBaseStartUpDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// AbilitySystemComponent에게 해당 어빌리티를 주는 메소드
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* ASC, int32 ApplyLevel = 1);

protected:
	// 
	void GrantAbilities(const TArray< TSubclassOf < UBaseGameplayAbility > >& InAbilitiesToGive, UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UBaseGameplayAbility > > startUpGameplayAbilities_;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UBaseGameplayAbility > > reactiveAbilities_;
};
