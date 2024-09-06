// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseStartUpDataAsset.generated.h"

class UActionRPGGameplayAbility;
class UActionRPGAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UBaseStartUpDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	void GrantAbilities(const TArray< TSubclassOf < UActionRPGGameplayAbility > >& InAbilitiesToGive, UActionRPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UActionRPGGameplayAbility > > m_ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UActionRPGGameplayAbility > > m_ReactiveAbilities;	
};
