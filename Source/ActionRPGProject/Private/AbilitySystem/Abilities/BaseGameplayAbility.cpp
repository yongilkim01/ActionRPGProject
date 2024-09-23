// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "Components/Combat/CombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

/**
 * 능력이 부여될 때 호출되는 메소드.
 *
 * 능력이 플레이어나 액터에게 부여될 때 호출되며,
 * EAP_OnGiven 정책을 따르는 경우 능력이 자동으로 활성화됨.
 *
 * @param ActorInfo - 능력을 받는 액터의 정보
 * @param Spec - 부여된 능력의 스펙
 */
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

FActiveGameplayEffectHandle UBaseGameplayAbility::ApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& inSpecHandle)
{
	UAbilitySystemComponent* targetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);

	check(targetASC && inSpecHandle.IsValid());

	return GetActionRPGAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		*inSpecHandle.Data,
		targetASC
	);
}

FActiveGameplayEffectHandle UBaseGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* targetActor, const FGameplayEffectSpecHandle& inSpecHandle, EActionRPGSuccessType& outSuccessType)
{
	FActiveGameplayEffectHandle activeGameplayEffectHandle = ApplyEffectSpecHandleToTarget(targetActor, inSpecHandle);
	outSuccessType = activeGameplayEffectHandle.WasSuccessfullyApplied() ? EActionRPGSuccessType::EAS_Successful : EActionRPGSuccessType::EAS_Failed;
	return activeGameplayEffectHandle;
}

UCombatComponent* UBaseGameplayAbility::GetCombatComponent() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UCombatComponent>();
}

UActionRPGAbilitySystemComponent* UBaseGameplayAbility::GetActionRPGAbilitySystemComponent() const
{
	return Cast<UActionRPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

