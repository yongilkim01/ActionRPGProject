// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionRPGFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"

UActionRPGAbilitySystemComponent* UActionRPGFunctionLibrary::GetActionRPGASCFromActorInfo(AActor* inActor)
{
	check(inActor);

	return CastChecked<UActionRPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(inActor));


}

void UActionRPGFunctionLibrary::AddGameplayTagToActorIfNone(AActor* inActor, FGameplayTag inTagToAdd)
{
	UActionRPGAbilitySystemComponent* asc = GetActionRPGASCFromActorInfo(inActor);

	if (!asc->HasMatchingGameplayTag(inTagToAdd))
	{
		asc->AddLooseGameplayTag(inTagToAdd);
	}
}

void UActionRPGFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* inActor, FGameplayTag inTagToRemove)
{
	UActionRPGAbilitySystemComponent* asc = GetActionRPGASCFromActorInfo(inActor);

	if (asc->HasMatchingGameplayTag(inTagToRemove))
	{
		asc->RemoveLooseGameplayTag(inTagToRemove);
	}
}

bool UActionRPGFunctionLibrary::IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck)
{
	UActionRPGAbilitySystemComponent* asc = GetActionRPGASCFromActorInfo(inActor);

	return asc->HasMatchingGameplayTag(inTagToCheck);
}

void UActionRPGFunctionLibrary::BP_IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck, EActionRPGConfirmType& outConfirmType)
{
	outConfirmType = IsActorHaveTag(inActor, inTagToCheck) ? EActionRPGConfirmType::EAC_Yes : EActionRPGConfirmType::EAC_No;
}
