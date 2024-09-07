// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PlayerCharacter.generated.h"

class UActionRPGAbilitySystemComponent;
class UActionRPGAttributeSet;
class UBaseStartUpDataAsset;

UCLASS()
class ACTIONRPGPROJECT_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public: // Public method
	APlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;

public: // Geteer Setter
	FORCEINLINE UActionRPGAbilitySystemComponent* GetActionRPGAbilitySystemComponent() const { return m_ActionRPGAbilitySystemComponent; }
	FORCEINLINE UActionRPGAttributeSet* GetActionRPGAttributesSet() const { return m_ActionRPGAttributeSet; }

protected: // Protected variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UActionRPGAbilitySystemComponent* m_ActionRPGAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UActionRPGAttributeSet* m_ActionRPGAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UBaseStartUpDataAsset> m_CharacterStartUpData;
};
