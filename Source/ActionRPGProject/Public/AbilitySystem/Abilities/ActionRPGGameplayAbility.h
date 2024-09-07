// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ActionRPGGameplayAbility.generated.h"


UENUM(BlueprintType)
enum class EActionRPGAbilityActivationPolicy : uint8
{
	EAP_OnTriggered,
	EAP_OnGiven
};
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EActionRPGAbilityActivationPolicy m_AbilityActivationPolicy = EActionRPGAbilityActivationPolicy::EAP_OnTriggered;
};
