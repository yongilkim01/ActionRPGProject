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
	// Ability system component���� ���� �����͸� �����ϴ� �������̵� �޼ҵ�
	virtual void GiveToAbilitySystemComponent(UActionRPGAbilitySystemComponent* ASC, int32 ApplyLevel = 1) override;

private:
	// S
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> playerAbilitySets_;
	
};
