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
	// UGameplayAbility 클래스 상속 인터페이스
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityActivationPolicy abilityActivationPolicy_ = EAbilityActivationPolicy::EAP_OnTriggered;

public: // Getter Setter
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UCombatComponent* GetCombatComponent() const;

	// Ability system component를 반환하는 메소드
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UActionRPGAbilitySystemComponent* GetActionRPGAbilitySystemComponent() const;
};
