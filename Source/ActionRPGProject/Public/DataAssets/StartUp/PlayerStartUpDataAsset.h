// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "ActionRPGTypes/ActionRPGStructTypes.h"
#include "PlayerStartUpDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UPlayerStartUpDataAsset : public UBaseStartUpDataAsset
{
	GENERATED_BODY()

public:
	// Ability system component을 반환하는 메소드
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* ASC, int32 ApplyLevel = 1) override;

private:
	// S
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> playerAbilitySets_;
	
};
