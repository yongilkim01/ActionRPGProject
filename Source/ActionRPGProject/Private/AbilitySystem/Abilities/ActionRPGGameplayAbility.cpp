// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ActionRPGGameplayAbility.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"

void UActionRPGGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (m_AbilityActivationPolicy == EActionRPGAbilityActivationPolicy::EAP_OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UActionRPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (m_AbilityActivationPolicy == EActionRPGAbilityActivationPolicy::EAP_OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}
