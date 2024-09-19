// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionRPGFunctionLibrary.generated.h"

class UActionRPGAbilitySystemComponent;

UENUM()
enum class EActionRPGConfirmType : uint8
{
	EAC_Yes,
	EAC_No
};
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UActionRPGAbilitySystemComponent* GetActionRPGASCFromActorInfo(AActor* inActor);
	
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* inActor, FGameplayTag inTagToAdd);

	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* inActor, FGameplayTag inTagToRemove);

	static bool IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck);

	UFUNCTION(BlueprintCallable, Category = "ActionRPG|FunctionLibrary", meta = (DisplayName = "Is Actor Have Tag", ExpandEnumAsExecs = "outConfirmType"))
	static void BP_IsActorHaveTag(AActor* inActor, FGameplayTag inTagToCheck, EActionRPGConfirmType& outConfirmType);
};