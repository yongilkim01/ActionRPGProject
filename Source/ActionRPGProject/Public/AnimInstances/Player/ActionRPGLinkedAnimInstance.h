// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ActionRPGAnimInstance.h"
#include "ActionRPGLinkedAnimInstance.generated.h"

class UActionRPGPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGLinkedAnimInstance : public UActionRPGAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UActionRPGPlayerAnimInstance* GetPlayerAnimInstance() const;
	
};
