// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_Input.h"
#include "ActionRPGInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_Input* inInputConfig, const FGameplayTag& inInputTag, ETriggerEvent triggerEvent, UserObject* contextObj, CallbackFunc func);
	
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
