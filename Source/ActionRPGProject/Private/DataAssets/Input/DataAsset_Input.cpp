// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_Input.h"

UInputAction* UDataAsset_Input::FindNativeInputActionByTag(const FGameplayTag& inInputTag) const
{
    for (const FActionRPGInputConfig& inputActionConfig : m_NativeInputActions)
    {
        if (inputActionConfig.m_InputTag == inInputTag && inputActionConfig.m_InputAction)
        {
            return inputActionConfig.m_InputAction;
        }
    }
    return nullptr;
}
