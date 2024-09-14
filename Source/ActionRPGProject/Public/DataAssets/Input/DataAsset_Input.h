// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_Input.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FInputConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag inputTag_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* inputAction_;

	bool IsValid() const
	{
		return inputTag_.IsValid() && inputAction_;
	}
};

/**
 *  Input binding process
 *  Define input tags(current file) -> mapping input tag with input action -> define input binding method -> define input callback -> fill need function method
 */
UCLASS()
class ACTIONRPGPROJECT_API UDataAsset_Input : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputAction* FindNativeInputActionByTag(const FGameplayTag&) const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* inputMappingContext_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FInputConfig> nativeInputActions_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FInputConfig> actionInputActions_;

};
