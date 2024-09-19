// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

class UCombatComponent;
class UActionRPGAbilitySystemComponent;

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	EAP_OnTriggered,
	EAP_OnGiven
};
/**
 *
 */
UCLASS()
class ACTIONRPGPROJECT_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// UGameplayAbility Ŭ���� ��� �������̽�
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityActivationPolicy abilityActivationPolicy_ = EAbilityActivationPolicy::EAP_OnTriggered;

public: // Getter Setter
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UCombatComponent* GetCombatComponent() const;

	// Ability system component�� ��ȯ�ϴ� �޼ҵ�
	UFUNCTION(BlueprintPure, Category = "ActionRPG|Ability")
	UActionRPGAbilitySystemComponent* GetActionRPGAbilitySystemComponent() const;
};
