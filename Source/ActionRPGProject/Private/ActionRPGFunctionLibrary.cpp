// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionRPGFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/Combat/CombatComponent.h"
#include "Interfaces/BaseCombatInterface.h"
#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"

UActionRPGAbilitySystemComponent* UActionRPGFunctionLibrary::GetActionRPGASCFromActorInfo(AActor* inActor)
{
	// inActor가 유효한지 확인
	check(inActor);

	// inActor에서 AbilitySystemComponent를 가져와 ActionRPG 전용 ASC로 캐스팅하여 반환
	return CastChecked<UActionRPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(inActor));
}

void UActionRPGFunctionLibrary::AddGameplayTagToActorIfNone(AActor* inActor, FGameplayTag inTagToAdd)
{
	// 주어진 액터에서 ActionRPG ASC를 가져옴
	UActionRPGAbilitySystemComponent* asc = GetActionRPGASCFromActorInfo(inActor);

	// 액터가 해당 태그를 가지고 있지 않다면 태그 추가
	if (!asc->HasMatchingGameplayTag(inTagToAdd))
	{
		asc->AddLooseGameplayTag(inTagToAdd);
	}
}

void UActionRPGFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* inActor, FGameplayTag inTagToRemove)
{
	// 주어진 액터에서 ActionRPG ASC를 가져옴
	UActionRPGAbilitySystemComponent* asc = GetActionRPGASCFromActorInfo(inActor);

	// 액터가 해당 태그를 가지고 있다면 태그 제거
	if (asc->HasMatchingGameplayTag(inTagToRemove))
	{
		asc->RemoveLooseGameplayTag(inTagToRemove);
	}
}

bool UActionRPGFunctionLibrary::IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck)
{
	// 주어진 액터에서 ActionRPG ASC를 가져옴
	UActionRPGAbilitySystemComponent* asc = GetActionRPGASCFromActorInfo(inActor);

	// 액터가 해당 태그를 가지고 있는지 여부를 반환
	return asc->HasMatchingGameplayTag(inTagToCheck);
}

/**
* 블루프린트에서 사용 가능한 함수로, 액터가 주어진 태그를 가지고 있는지 확인하여
* EActionRPGConfirmType 값(EAC_Yes 또는 EAC_No)으로 반환
*
* @param inActor - 태그를 확인할 액터
* @param inTagToCheck - 확인할 태그
* @param outConfirmType - 태그 여부를 반환할 변수
*/
void UActionRPGFunctionLibrary::BP_IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck, EActionRPGConfirmType& outConfirmType)
{
	// 액터가 태그를 가지고 있으면 EAC_Yes, 없으면 EAC_No를 반환
	outConfirmType = IsActorHaveTag(inActor, inTagToCheck) ? EActionRPGConfirmType::EAC_Yes : EActionRPGConfirmType::EAC_No;
}

/**
* 주어진 액터에서 CombatComponent를 가져옴
* 액터가 IBaseCombatInterface 인터페이스를 구현하는지 확인하고,
* 구현할 경우 CombatComponent를 반환
*
* @param inActor - CombatComponent를 가져올 액터
* @return UCombatComponent* - CombatComponent를 반환 (없을 경우 nullptr 반환)
*/
UCombatComponent* UActionRPGFunctionLibrary::GetCombatComponentFromActor(AActor* inActor)
{
	// inActor가 유효한지 확인
	check(inActor);

	// 액터가 IBaseCombatInterface 인터페이스를 구현하는지 확인
	if (IBaseCombatInterface* baseCombatInterface = Cast<IBaseCombatInterface>(inActor))
	{
		// CombatComponent 객체를 반환
		return baseCombatInterface->GetCombatComponent();
	}

	// CombatComponent를 찾지 못한 경우 nullptr 반환
	return nullptr;
}

/**
* 블루프린트에서 사용 가능한 함수로, 액터에서 CombatComponent를 가져와
* 유효성을 EActionRPGValidType 값(EAV_Valid 또는 EAV_InValid)으로 반환
*
* @param inActor - CombatComponent를 확인할 액터
* @param outValidType - CombatComponent의 유효성 여부를 반환할 변수
* @return UCombatComponent* - CombatComponent를 반환 (없을 경우 nullptr 반환)
*/
UCombatComponent* UActionRPGFunctionLibrary::BP_GetCombatComponentFromActor(AActor* inActor, EActionRPGValidType& outValidType)
{
	// 주어진 액터에서 CombatComponent를 가져옴
	UCombatComponent* combatComponent = GetCombatComponentFromActor(inActor);

	// CombatComponent의 유효성 여부에 따라서 ActionRPGValidType 값을 할당
	outValidType = combatComponent ? EActionRPGValidType::EAV_Valid : EActionRPGValidType::EAV_InValid;

	// CombatComponent를 반환
	return combatComponent;
}
