// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "GameplayTagContainer.h"
#include "PlayerStartUpDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag inputTag_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseGameplayAbility> gameplayAbility_;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UPlayerStartUpDataAsset : public UBaseStartUpDataAsset
{
	GENERATED_BODY()

public:
	// Ability system component에게 시작 데이터를 전달하는 오버라이드 메소드
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* ASC, int32 ApplyLevel = 1) override;

private:
	// S
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> playerAbilitySets_;
	
};
