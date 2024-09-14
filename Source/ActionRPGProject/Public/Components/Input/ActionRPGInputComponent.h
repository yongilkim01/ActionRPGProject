// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_Input.h"
#include "ActionRPGInputComponent.generated.h"

/**
 *  Input binding process
 *  Define input tags -> mapping input tag with input action(current file) -> define input binding method -> define input callback -> fill need function method
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_Input* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObj, CallbackFunc Func);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_Input* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UActionRPGInputComponent::BindNativeInputAction(const UDataAsset_Input* inInputConfig, const FGameplayTag& inInputTag, ETriggerEvent triggerEvent, UserObject* contextObj, CallbackFunc func)
{
	checkf(inInputConfig, TEXT("Input config data asset is null"));

	if (UInputAction* foundAction = inInputConfig->FindNativeInputActionByTag(inInputTag))
	{
		BindAction(foundAction, triggerEvent, contextObj, func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UActionRPGInputComponent::BindAbilityInputAction(const UDataAsset_Input* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null"));

	for (const FInputConfig& AbilityInputActionConfig : InInputConfig->actionInputActions_)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.inputAction_, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.inputTag_);
		BindAction(AbilityInputActionConfig.inputAction_, ETriggerEvent::Completed, ContextObject, InputRelasedFunc, AbilityInputActionConfig.inputTag_);
	}
}