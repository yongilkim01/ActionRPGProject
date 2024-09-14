// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_Input.h"

UInputAction* UDataAsset_Input::FindNativeInputActionByTag(const FGameplayTag& inInputTag) const
{
    for (const FInputConfig& inputActionConfig : nativeInputActions_)
    {
        if (inputActionConfig.inputTag_ == inInputTag && inputActionConfig.inputAction_)
        {
            return inputActionConfig.inputAction_;
        }
    }
    return nullptr;
}
