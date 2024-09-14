// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

/**
* Input binding process
* Define input tags(current file) -> mapping input tag with input action -> define input binding method -> define input callback -> fill need function method
*/

namespace ActionRPGGameplayTags
{
	// Input tag
	ACTIONRPGPROJECT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ACTIONRPGPROJECT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	ACTIONRPGPROJECT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip);
	ACTIONRPGPROJECT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquip);

	// Player tag
	ACTIONRPGPROJECT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
}