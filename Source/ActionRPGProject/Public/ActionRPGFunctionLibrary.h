// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionRPGTypes/ActionRPGEnumTypes.h"
#include "ActionRPGFunctionLibrary.generated.h"

class UActionRPGAbilitySystemComponent;
class UCombatComponent;

/**
 * ActionRPG에서 사용할 함수들을 제공하는 블루프린트 함수 라이브러리 클래스
 * 다양한 액터 관련 기능을 제공하며, 특히 태그 및 컴포넌트 관리 기능을 포함함
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 주어진 액터로부터 UActionRPGAbilitySystemComponent를 가져오는 함수
	 *
	 * @param inActor - ASC를 가져올 액터
	 * @return UActionRPGAbilitySystemComponent* - 가져온 ASC
	 */
	static UActionRPGAbilitySystemComponent* GetActionRPGASCFromActorInfo(AActor* inActor);
	
	/**
	 * 액터에 특정 태그가 없을 경우 해당 태그를 추가하는 함수
	 *
	 * @param inActor - 태그를 추가할 액터
	 * @param inTagToAdd - 추가할 태그
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* inActor, FGameplayTag inTagToAdd);

	/**
	 * 액터에 특정 태그가 존재할 경우 해당 태그를 제거하는 함수
	 *
	 * @param inActor - 태그를 제거할 액터
	 * @param inTagToRemove - 제거할 태그
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* inActor, FGameplayTag inTagToRemove);

	/**
	 * 액터가 특정 태그를 가지고 있는지 확인하는 함수
	 *
	 * @param inActor - 태그를 확인할 액터
	 * @param inTagToCheck - 확인할 태그
	 * @return bool - 액터가 해당 태그를 가지고 있으면 true, 없으면 false
	 */
	static bool IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck);

	/**
	 * 블루프린트에서 사용할 수 있는 함수로, 액터가 주어진 태그를 가지고 있는지 확인하고
	 * EActionRPGConfirmType을 반환
	 *
	 * @param inActor - 태그를 확인할 액터
	 * @param inTagToCheck - 확인할 태그
	 * @param outConfirmType - 태그 존재 여부를 반환할 EActionRPGConfirmType 값
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary", meta = (DisplayName = "Is Actor Have Tag", ExpandEnumAsExecs = "outConfirmType"))
	static void BP_IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck, EActionRPGConfirmType& outConfirmType);

	/**
	 * 주어진 액터로부터 UCombatComponent를 가져오는 함수
	 * IBaseCombatInterface를 구현한 액터를 대상으로 Combat Component를 가져옴
	 *
	 * @param inActor - Combat Component를 가져올 액터
	 * @return UCombatComponent* - 가져온 Combat Component (없을 경우 nullptr 반환)
	 */
	static UCombatComponent* GetCombatComponentFromActor(AActor* inActor);

	/**
	 * 블루프린트에서 사용할 수 있는 함수로, 액터의 Combat Component를 가져와
	 * 유효성을 EActionRPGValidType으로 반환
	 *
	 * @param inActor - Combat Component를 가져올 액터
	 * @param outValidType - 컴포넌트의 유효성 여부를 반환할 EActionRPGValidType 값
	 * @return UCombatComponent* - 가져온 Combat Component (없을 경우 nullptr 반환)
	 */
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary", meta = (DisplayName = "Get Combat Component From Actor", ExpandEnumAsExecs = "outValidType"))
	static UCombatComponent* BP_GetCombatComponentFromActor(AActor* inActor, EActionRPGValidType& outValidType);
};