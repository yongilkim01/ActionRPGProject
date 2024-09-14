// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "Components/Combat/CombatComponent.h"

// Actor에게 ability를 주는 메소드
void UBaseGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (abilityActivationPolicy_ == EAbilityActivationPolicy::EAP_OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UBaseGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (abilityActivationPolicy_ == EAbilityActivationPolicy::EAP_OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UCombatComponent* UBaseGameplayAbility::GetCombatComponent() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UCombatComponent>();
}

UActionRPGAbilitySystemComponent* UBaseGameplayAbility::GetActionRPGAbilitySystemComponent() const
{
	return Cast<UActionRPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

