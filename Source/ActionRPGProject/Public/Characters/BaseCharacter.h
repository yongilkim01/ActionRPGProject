// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UActionRPGAbilitySystemComponent;
class UActionRPGAttributeSet;
class UBaseStartUpDataAsset;

UCLASS()
class ACTIONRPGPROJECT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public: // Public method
	ABaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;

public: // Geteer Setter
	FORCEINLINE UActionRPGAbilitySystemComponent* GetActionRPGAbilitySystemComponent() const { return characterAbilitySystemComponent_; }
	FORCEINLINE UActionRPGAttributeSet* GetActionRPGAttributesSet() const { return characterAttributeSet_; }

protected: // Protected variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UActionRPGAbilitySystemComponent* characterAbilitySystemComponent_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UActionRPGAttributeSet* characterAttributeSet_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UBaseStartUpDataAsset> characterStartUpData_;

};
